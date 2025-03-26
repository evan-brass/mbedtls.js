# NOTE: -lc-printscan-long-double removes an error message that would otherwise potentially be written to stderr.  That error message resulted in the __stdio_write/_seek/_close functions being imported from wasi.

COMMON = -Ic-src -Ivendor/include \
	-DMBEDTLS_USER_CONFIG_FILE=\"config.h\"

src/mbedtls.wasm: c-src/* vendor/include/* vendor/library/*
	wasm32-wasi-clang -E -dM \
		$(COMMON) \
		c-src/defines.h \
	| sed -n -E 's/^#define MBEDTLS_([A-Z0-9_]+)( +)((-?0x[0-9A-F]+)|(-?[0-9]+)|("[^"]*"))/export const \1 =\2\3;/p' > src/defines.js
	wasm32-wasi-clang -O3 \
		$(COMMON) \
		-fvisibility=default \
		-mexec-model=reactor \
		-mmultivalue \
		-Wl,-lc-printscan-long-double,--export-table,--growable-table,--export-dynamic,--no-entry,--allow-undefined \
		-Wl,--export=malloc,--export=free,--export=strlen \
		-o $@ \
		$(filter %.c, $^)
	wasm-tools print $@ | grep -E "import|export" > symbols.txt
