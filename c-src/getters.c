#define MBEDTLS_ALLOW_PRIVATE_ACCESS
#include "mbedtls/x509_crt.h"
#include "mbedtls/ssl.h"

__attribute__((import_module("./memory.js"))) __externref_t get_buffer(unsigned char * ptr, size_t len);
__attribute__((import_module("./console.js"))) void mbedtls_debug(void *, int, const char *, int, const char *);

__externref_t get_mbedtls_x509_crt_raw(mbedtls_x509_crt* crt) {
	return get_buffer(crt->raw.p, crt->raw.len);
}

__externref_t get_mbedtls_ssl_context_recv(mbedtls_ssl_context* ssl) {
	__externref_t ret = get_buffer(ssl->recv_ptr, ssl->recv_len);
	ssl->recv_ptr = NULL;
	ssl->recv_len = 0;
	return ret;
}
int* get_mbedtls_ssl_context_recv_res(mbedtls_ssl_context* ssl) {
	return &ssl->recv_res;
}
__externref_t get_mbedtls_ssl_context_send(mbedtls_ssl_context* ssl) {
	__externref_t ret = get_buffer((unsigned char*) ssl->send_ptr, ssl->send_len);
	ssl->send_ptr = NULL;
	ssl->send_len = 0;
	return ret;
}
int* get_mbedtls_ssl_context_send_res(mbedtls_ssl_context* ssl) {
	return &ssl->send_res;
}

void set_mbedtls_ssl_config_dbg(mbedtls_ssl_config* conf) {
	mbedtls_ssl_conf_dbg(conf, mbedtls_debug, NULL);
}
