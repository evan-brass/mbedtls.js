
src/mbedtls.wasm: c-src/* vendor/include/* vendor/library/*
	wasm32-wasi-clang -O3 \
		-Ic-src -Ivendor/include \
		-DMBEDTLS_CONFIG_FILE=\"config.h\" \
		-fvisibility=default \
		-mexec-model=reactor \
		-Wl,--export-dynamic,--no-entry \
		-o $@ \
		$(filter %.c, $^)
	wasm-tools print $@ | grep -E "import|export" > symbols.txt
