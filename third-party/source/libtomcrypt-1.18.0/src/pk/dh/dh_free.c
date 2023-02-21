/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 */

#include "tomcrypt.h"

#ifdef LTC_MDH

/**
  Free the allocated ram for a DH key
  @param key   The key which you wish to free
*/
void dh_free(dh_key *key)
{
   LTC_ARGCHKVD(key != NULL);
   mp_cleanup_multi(&key->prime, &key->base, &key->y, &key->x, NULL);
}

#endif /* LTC_MDH */

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
