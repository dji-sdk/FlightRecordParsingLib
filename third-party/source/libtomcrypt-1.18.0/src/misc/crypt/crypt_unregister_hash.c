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
  @file crypt_unregister_hash.c
  Unregister a hash, Tom St Denis
*/

/**
  Unregister a hash from the descriptor table
  @param hash   The hash descriptor to remove
  @return CRYPT_OK on success
*/
int unregister_hash(const struct ltc_hash_descriptor *hash)
{
   int x;

   LTC_ARGCHK(hash != NULL);

   /* is it already registered? */
   LTC_MUTEX_LOCK(&ltc_hash_mutex);
   for (x = 0; x < TAB_SIZE; x++) {
       if (XMEMCMP(&hash_descriptor[x], hash, sizeof(struct ltc_hash_descriptor)) == 0) {
          hash_descriptor[x].name = NULL;
          LTC_MUTEX_UNLOCK(&ltc_hash_mutex);
          return CRYPT_OK;
       }
   }
   LTC_MUTEX_UNLOCK(&ltc_hash_mutex);
   return CRYPT_ERROR;
}

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
