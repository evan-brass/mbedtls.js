import { decoder, OutOfMemoryError } from './util.js';
import * as defines from './defines.js';

export const { instance: { exports }, module } = await WebAssembly.instantiateStreaming(fetch(new URL('./mbedtls.wasm', import.meta.url)), {
	'./time.js': {
		date_now(ptr) {
			const now = Date.now();
			if (ptr) {
				memdv(ptr).setFloat64(0, now, true);
			}
			return now;
		},
		performance_now() {
			return performance.now();
		},
		utc_is_past(x509_time) {
			return read_x509_time(x509_time) < Date.now();
		},
		utc_is_future(x509_time) {
			return read_x509_time(x509_time) > Date.now();
		}
	},
	'./crypto.js': {
		get_random_values(_null, ptr, len, out_len) {
			// NOTE: Technically, getRandomValues is not guaranteed to be cryptographically secure... You should probably use a wrapping (CTR|HMAC)_DRBG and hope for the best.
			crypto.getRandomValues(mem8(ptr, len));
			memdv(out_len).setUint32(0, len, true); // Evan, don't forget the load bearing "true" that means LITTLE ENDIAN you fucking dipshit.
			return 0; // Infallible
		}
	},
	'./memory.js': {
		get_buffer(ptr, len) {
			return new Uint8Array(exports.memory.buffer, ptr, len);
		}
	},
	'./console.js': {
		mbedtls_debug(_ctx, level, file_ptr, line, msg_ptr) {
			const [file, msg] = [file_ptr, msg_ptr].map(p => decoder.decode(mem8(p, exports.strlen(p))));
			console.log(`${file}:${line} - ${msg}`);
		}
	}
});

export const mbedtls = { ...defines };
for (const key in exports) {
	const new_key = key.replace(/mbedtls_/, '');
	mbedtls[new_key] = exports[key];
}

exports._initialize();

const indirect = mbedtls.__indirect_function_table;
const created = new Map(); // wasm wrapper func -> index

export function func_ptr(func) {
	const index = indirect.length;
	indirect.grow(1);
	created.set(index, func);
	indirect.set(index, func);
	return index;
}

function read_x509_time(ptr) {
	const dv = memdv(ptr);
	return Date.UTC(
		// Possibly may need to add offset the
		/* year, mon, day, hour, min, sec */
		...Array.from([
			// year, month, day,
			0, 0, 0,
			// hour, min, sec,
			0, 0, 0,
		], (offset, i) => dv.getInt32(4 * i + offset, true))
	);
}

export function check_non_null(res) {
	if (res == 0) {
		throw new OutOfMemoryError();
	}
	return check(res);
}
export function check(res) {
	if (res < 0) {
		throw new Error(`mbedtls Error (${res}): ${cstr(mbedtls.high_level_strerr(res)) || 'UNKNOWN ERROR CODE'} - ${mbedtls.low_level_strerr(res)}`);
	}
	return res;
}
export function cstr(ptr) {
	const len = mbedtls.strlen(ptr);
	return decoder.decode(mem8(ptr, len));
}
export function mem8(...args) {
	return new Uint8Array(mbedtls.memory.buffer, ...args);
}
export function memdv(...args) {
	return new DataView(mbedtls.memory.buffer, ...args);
}
