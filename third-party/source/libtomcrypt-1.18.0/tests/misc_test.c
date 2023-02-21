/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include  <tomcrypt_test.h>

int misc_test(void)
{
#ifdef LTC_HKDF
   DO(hkdf_test());
#endif
#ifdef LTC_PKCS_5
   DO(pkcs_5_test());
#endif
#ifdef LTC_BASE64
   DO(base64_test());
#endif
#ifdef LTC_ADLER32
   DO(adler32_test());
#endif
#ifdef LTC_CRC32
   DO(crc32_test());
#endif
   return 0;
}

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
