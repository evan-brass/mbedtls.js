import { decoder } from './util.js';

export const { instance: { exports: mbedtls }, module } = await WebAssembly.instantiateStreaming(fetch(new URL('./mbedtls.wasm', import.meta.url)), {
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
	}
});
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

export function check(res) {
	if (res < 0) {
		throw new Error(`mbedtls Error (${res}): ${cstr(mbedtls.mbedtls_high_level_strerr(res)) || 'UNKNOWN ERROR CODE'} - ${mbedtls.mbedtls_low_level_strerr(res)}`);
	}
}
export function cstr(ptr) {
	const len = mbedtls.strlen(ptr);
	return decoder.decode(mem8(ptr, len));
}
export function mem8(...args) {
	return new Uint8Array(mbedtls.memory.buffer, ...args);
}
export function memdv(...args) {
	return new DataView(offset.memory.buffer, ...args);
}
