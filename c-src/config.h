// We're going to need to overwrite a lot of stuff...
#define MBEDTLS_PLATFORM_C

// Support time and date, but we want to use javascript imports not wasi syscalls
#define MBEDTLS_HAVE_TIME
#define MBEDTLS_HAVE_TIME_DATE

// We won't support tls1.3 so ms_time won't even be used, but this is how it should be
#define MBEDTLS_PLATFORM_MS_TIME_ALT
#define MBEDTLS_PLATFORM_MS_TIME_TYPE_MACRO double
#define MBEDTLS_PLATFORM_MS_TIME_MACRO js_performance_now
__attribute__((import_module("./time.js"))) double js_performance_now(void);

// #define MBEDTLS_PLATFORM_TIME_ALT
#define MBEDTLS_PLATFORM_TIME_TYPE_MACRO double
#define MBEDTLS_PLATFORM_TIME_MACRO js_date_now
__attribute__((import_module("./time.js"))) double js_date_now(double*);

// The end goal is to remove gmtime altogether and to import the x509 is_past and is_future functions directly, I believe that those are the only places where gmtime is actually needed
#define MBEDTLS_PLATFORM_GMTIME_R_ALT
#define MBEDTLS_PLATFORM_GMTIME_R_MACRO() (void);
