#include <stdlib.h>
#include "mbedtls/x509_crt.h"
#include "mbedtls/pk.h"
#include "mbedtls/ssl.h"

#define CONSTR(objtype) objtype* new_ ## objtype() { \
	objtype* ret = (objtype*)malloc(sizeof(objtype)); \
	if (ret == NULL) return ret; \
	objtype ## _init(ret); \
	return ret; \
}

CONSTR(mbedtls_x509_crt);

#define mbedtls_pk_context_init mbedtls_pk_init
CONSTR(mbedtls_pk_context);

CONSTR(mbedtls_ssl_config);
#define mbedtls_ssl_context_init mbedtls_ssl_init
CONSTR(mbedtls_ssl_context);
