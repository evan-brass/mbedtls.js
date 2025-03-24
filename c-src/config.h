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

// TODO: I intend to remove gmtime_r entirely and then import javascript is_past and is_future functions
#define MBEDTLS_PLATFORM_GMTIME_R_ALT
#define MBEDTLS_PLATFORM_GMTIME_R_MACRO mbedtls_platform_gmtime_r
__attribute__((import_module("./time.js"),import_name("gmtime"))) struct tm *mbedtls_platform_gmtime_r(const double *tt, struct tm *tm_buf);

#define MBEDTLS_PLATFORM_SNPRINTF_MACRO snprintf

// I think mbedtls_printf is called directly by mbedtls_ssl_config_defaults and ssl_check_no_sig_alg_duplication
#define MBEDTLS_PLATFORM_PRINTF_MACRO(...)

#define MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK

#undef MBEDTLS_FS_IO
#undef MBEDTLS_NET_IO
#undef MBEDTLS_PSA_ITS_FILE_C
#undef MBEDTLS_NET_C
#undef MBEDTLS_ENTROPY_C
#undef MBEDTLS_PSA_CRYPTO_C
#undef MBEDTLS_LMS_C
#undef MBEDTLS_PSA_CRYPTO_STORAGE_C
#undef MBEDTLS_SSL_PROTO_TLS1_3
#undef MBEDTLS_TIMING_C
#undef MBEDTLS_SELF_TEST
