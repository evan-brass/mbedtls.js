export const { instance: { exports: mbedtls }, module } = await WebAssembly.instantiateStreaming(fetch(new URL('./mbedtls.wasm', import.meta.url)), {
	'./time.js': {
		date_now(_ptr) {
			// Also need to write the date into ptr
			return Date.now();
		},
		performance_now() {
			return performance.now();
		},
		gmtime(t, buf) {
			// TODO:
			return null;
		}
	}
});

export function mem8(...args) {
	return new Uint8Array(mbedtls.memory.buffer, ...args);
}
export function memdv(...args) {
	return new DataView(offset.memory.buffer, ...args);
}
