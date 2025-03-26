#include "mbedtls/x509_crt.h"

__attribute__((import_module("./memory.js"))) __externref_t get_buffer(unsigned char * ptr, size_t len);

__externref_t buf_mbedtls_x509_crt_raw(mbedtls_x509_crt* crt) {
	return get_buffer(crt->raw.p, crt->raw.len);
}
