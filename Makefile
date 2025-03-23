# NOTE: -lc-printscan-long-double removes an error message that would otherwise potentially be written to stderr.  That error message resulted in the __stdio_write/_seek/_close functions being imported from wasi.

src/mbedtls.wasm: c-src/* vendor/include/* vendor/library/*
	wasm32-wasi-clang -O3 \
		-Ic-src -Ivendor/include \
		-DMBEDTLS_USER_CONFIG_FILE=\"config.h\" \
		-fvisibility=default \
		-mexec-model=reactor \
		-Wl,-lc-printscan-long-double,--export-dynamic,--no-entry,--allow-undefined,--export=malloc,--export=free,--export=strlen \
		-o $@ \
		$(filter %.c, $^)
	wasm-tools print $@ | grep -E "import|export" > symbols.txt
