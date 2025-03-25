#include <stdlib.h>
#include "mbedtls/x509_crt.h"
#include "mbedtls/pk.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/hmac_drbg.h"

#define CONSTR(objtype) CONSTR_INIT(objtype, objtype ## _init);

#define CONSTR_INIT(objtype, init_func) objtype* new_ ## objtype() { \
	objtype* ret = (objtype*)malloc(sizeof(objtype)); \
	if (ret == NULL) return ret; \
	init_func(ret); \
	return ret; \
}

CONSTR(mbedtls_x509_crt);
CONSTR_INIT(mbedtls_pk_context, mbedtls_pk_init);
CONSTR(mbedtls_ssl_config);
CONSTR_INIT(mbedtls_ssl_context, mbedtls_ssl_init);
CONSTR_INIT(mbedtls_entropy_context, mbedtls_entropy_init);
CONSTR_INIT(mbedtls_hmac_drbg_context, mbedtls_hmac_drbg_init);
