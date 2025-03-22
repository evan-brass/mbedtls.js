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

// TODO: Swap this out with AES_ALT implemented using subtle crypto?
#define MBEDTLS_AES_C

#define MBEDTLS_ARIA_C
#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C
#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C

#define MBEDTLS_CAMELLIA_C
#define MBEDTLS_CCM_C
#define MBEDTLS_CHACHA20_C
#define MBEDTLS_CHACHAPOLY_C

#define MBEDTLS_CIPHER_C
#define MBEDTLS_CIPHER_MODE_CBC
#define MBEDTLS_CIPHER_MODE_CFB
#define MBEDTLS_CIPHER_MODE_CTR
#define MBEDTLS_CIPHER_MODE_OFB
#define MBEDTLS_CIPHER_MODE_XTS

#define MBEDTLS_CMAC_C

#define MBEDTLS_CTR_DRBG_C
// #define MBEDTLS_DEBUG_C
#define MBEDTLS_DHM_C
#define MBEDTLS_ECDH_C
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECJPAKE_C

#define MBEDTLS_ECP_C
#define MBEDTLS_ECP_DP_SECP192R1_ENABLED
#define MBEDTLS_ECP_DP_SECP224R1_ENABLED
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#define MBEDTLS_ECP_DP_SECP384R1_ENABLED
#define MBEDTLS_ECP_DP_SECP521R1_ENABLED
#define MBEDTLS_ECP_DP_SECP192K1_ENABLED
#define MBEDTLS_ECP_DP_SECP224K1_ENABLED
#define MBEDTLS_ECP_DP_SECP256K1_ENABLED
#define MBEDTLS_ECP_DP_BP256R1_ENABLED
#define MBEDTLS_ECP_DP_BP384R1_ENABLED
#define MBEDTLS_ECP_DP_BP512R1_ENABLED

// #define MBEDTLS_ERROR_C
#define MBEDTLS_GCM_C
#define MBEDTLS_HKDF_C
#define MBEDTLS_HMAC_DRBG_C
#define MBEDTLS_MD_C
#define MBEDTLS_MD5_C

// OID uses snprintf which wasi-libc uses vfprintf to implement and since there's a virtual file there it seems to include the wasi file syscalls close/seek/write.  This issue also affect debug and error
// TODO: Rewrite oid to not use snprintf or rewrite snprintf to not use a virtual file
// #define MBEDTLS_OID_C

#define MBEDTLS_PEM_C
#define MBEDTLS_PK_C

// TODO: These require OID
// #define MBEDTLS_PKCS5_C
// #define MBEDTLS_PKCS7_C

// WEIRD: PKCS12 doesn't require OID, but PKCS5 and 7 do.  Also, check_config.h doesn't enforce OID_C for PKCS5 which results in undefined symbols when linking
#define MBEDTLS_PKCS12_C

// TODO: These require OID
// #define MBEDTLS_PK_PARSE_C
// #define MBEDTLS_PK_WRITE_C

#define MBEDTLS_POLY1305_C
#define MBEDTLS_RIPEMD160_C

// TODO: RSA require MBEDTLS_PKCS1_V21
// #define MBEDTLS_RSA_C

#define MBEDTLS_SHA1_C
#define MBEDTLS_SHA3_C
#define MBEDTLS_SHA256_C
#define MBEDTLS_SHA512_C

// #define MBEDTLS_SSL_CACHE_C
#define MBEDTLS_SSL_CLI_C
// #define MBEDTLS_SSL_COOKIE_C
// #define MBEDTLS_SSL_TICKET_C
