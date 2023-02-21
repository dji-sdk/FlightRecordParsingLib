/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */
#include "tomcrypt.h"

/**
  @file rsa_free.c
  Free an RSA key, Tom St Denis
*/

#ifdef LTC_MRSA

/**
  Free an RSA key from memory
  @param key   The RSA key to free
*/
void rsa_free(rsa_key *key)
{
   LTC_ARGCHKVD(key != NULL);
   mp_cleanup_multi(&key->q, &key->p, &key->qP, &key->dP, &key->dQ, &key->N, &key->d, &key->e, NULL);
}

#endif

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
