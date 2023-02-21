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
   @file ctr_done.c
   CTR implementation, finish chain, Tom St Denis
*/

#ifdef LTC_CTR_MODE

/** Terminate the chain
  @param ctr    The CTR chain to terminate
  @return CRYPT_OK on success
*/
int ctr_done(symmetric_CTR *ctr)
{
   int err;
   LTC_ARGCHK(ctr != NULL);

   if ((err = cipher_is_valid(ctr->cipher)) != CRYPT_OK) {
      return err;
   }
   cipher_descriptor[ctr->cipher].done(&ctr->key);
   return CRYPT_OK;
}



#endif

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
