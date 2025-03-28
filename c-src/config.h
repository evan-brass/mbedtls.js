#define MBEDTLS_JS
#define MBEDTLS_PLATFORM_NO_STD_FUNCTIONS

#include <stdio.h>
#include <time.h>

#define MBEDTLS_PLATFORM_MS_TIME_ALT
#define MBEDTLS_PLATFORM_MS_TIME_TYPE_MACRO double
__attribute__((import_module("./time.js"),import_name("performance_now"))) double mbedtls_ms_time(void);

#define MBEDTLS_PLATFORM_TIME_TYPE_MACRO double
#define MBEDTLS_PRINTF_MS_TIME d
#define MBEDTLS_PLATFORM_TIME_MACRO mbedtls_time
__attribute__((import_module("./time.js"),import_name("date_now"))) double mbedtls_time(double*);

#define MBEDTLS_NO_PLATFORM_ENTROPY
#define MBEDTLS_ENTROPY_HARDWARE_ALT
__attribute__((import_module("./crypto.js"), import_name("get_random_values"))) int mbedtls_hardware_poll(void *data, unsigned char *output, size_t len, size_t *olen);

#define MBEDTLS_PLATFORM_SNPRINTF_MACRO snprintf

// I think mbedtls_printf is called directly by mbedtls_ssl_config_defaults and ssl_check_no_sig_alg_duplication
#define MBEDTLS_PLATFORM_PRINTF_MACRO(...)

#define MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK
#define MBEDTLS_SSL_DTLS_SRTP
#define MBEDTLS_X509_REMOVE_INFO
#define MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH

#undef MBEDTLS_HAVE_ASM
#undef MBEDTLS_FS_IO
#undef MBEDTLS_NET_IO
#undef MBEDTLS_PSA_ITS_FILE_C
#undef MBEDTLS_NET_C
#undef MBEDTLS_PSA_CRYPTO_C
#undef MBEDTLS_LMS_C
#undef MBEDTLS_PSA_CRYPTO_STORAGE_C
#undef MBEDTLS_SSL_PROTO_TLS1_3
#undef MBEDTLS_TIMING_C
#undef MBEDTLS_SELF_TEST
