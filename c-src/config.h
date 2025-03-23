#define MBEDTLS_DEPRECATED_REMOVED

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
#define MBEDTLS_CIPHER_PADDING_PKCS7
#define MBEDTLS_CIPHER_PADDING_ONE_AND_ZEROS
#define MBEDTLS_CIPHER_PADDING_ZEROS_AND_LEN
#define MBEDTLS_CIPHER_PADDING_ZEROS

#define MBEDTLS_CMAC_C

#define MBEDTLS_CTR_DRBG_C
// #define MBEDTLS_DEBUG_C
#define MBEDTLS_DHM_C
#define MBEDTLS_ECDH_C

#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECDSA_DETERMINISTIC

#define MBEDTLS_ECJPAKE_C

#define MBEDTLS_ECP_C
#define MBEDTLS_ECP_NIST_OPTIM
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
#define MBEDTLS_PK_PARSE_EC_EXTENDED
#define MBEDTLS_PK_PARSE_EC_COMPRESSED

// TODO: These require OID
// #define MBEDTLS_PKCS5_C
// #define MBEDTLS_PKCS7_C
#define MBEDTLS_PKCS1_V15
#define MBEDTLS_PKCS1_V21

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

#define MBEDTLS_SSL_TLS_C
// #define MBEDTLS_SSL_CACHE_C
#define MBEDTLS_SSL_CLI_C
// #define MBEDTLS_SSL_COOKIE_C
// #define MBEDTLS_SSL_TICKET_C
#define MBEDTLS_SSL_ALL_ALERT_MESSAGES
#define MBEDTLS_SSL_DTLS_CONNECTION_ID
#define MBEDTLS_SSL_DTLS_CONNECTION_ID_COMPAT 0
#define MBEDTLS_SSL_CONTEXT_SERIALIZATION
#define MBEDTLS_SSL_ENCRYPT_THEN_MAC
#define MBEDTLS_SSL_EXTENDED_MASTER_SECRET
#define MBEDTLS_SSL_KEEP_PEER_CERTIFICATE
#define MBEDTLS_SSL_RENEGOTIATION
#define MBEDTLS_SSL_MAX_FRAGMENT_LENGTH
#define MBEDTLS_SSL_PROTO_TLS1_2
#define MBEDTLS_SSL_PROTO_DTLS
#define MBEDTLS_SSL_ALPN
#define MBEDTLS_SSL_DTLS_ANTI_REPLAY
#define MBEDTLS_SSL_DTLS_HELLO_VERIFY
#define MBEDTLS_SSL_DTLS_SRTP
#define MBEDTLS_SSL_DTLS_CLIENT_PORT_REUSE
#define MBEDTLS_SSL_VARIABLE_BUFFER_LENGTH

#define MBEDTLS_KEY_EXCHANGE_PSK_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_DHE_PSK_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_ECDHE_PSK_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_RSA_PSK_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_RSA_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_DHE_RSA_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_ECDHE_RSA_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_ECDHE_ECDSA_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_ECDH_ECDSA_ENABLED
// #define MBEDTLS_KEY_EXCHANGE_ECDH_RSA_ENABLED

#define MBEDTLS_X509_REMOVE_INFO
// #define MBEDTLS_X509_CREATE_C
// #define MBEDTLS_X509_CRL_C
// #define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_C
// #define MBEDTLS_X509_CRT_PARSE_C
// #define MBEDTLS_X509_CSR_C
#define MBEDTLS_X509_WRITE_CRT_C
// #define MBEDTLS_X509_WRITE_CSR_C
// #define MBEDTLS_X509_WRITE_C
// #define MBEDTLS_X509_TRUSTED_CERTIFICATE_CALLBACK

#define MBEDTLS_GENPRIME
