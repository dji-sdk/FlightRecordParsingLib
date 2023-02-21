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
   @file cfb_getiv.c
   CFB implementation, get IV, Tom St Denis
*/

#ifdef LTC_CFB_MODE

/**
   Get the current initialization vector
   @param IV   [out] The destination of the initialization vector
   @param len  [in/out]  The max size and resulting size of the initialization vector
   @param cfb  The CFB state
   @return CRYPT_OK if successful
*/
int cfb_getiv(unsigned char *IV, unsigned long *len, symmetric_CFB *cfb)
{
   LTC_ARGCHK(IV  != NULL);
   LTC_ARGCHK(len != NULL);
   LTC_ARGCHK(cfb != NULL);
   if ((unsigned long)cfb->blocklen > *len) {
      *len = cfb->blocklen;
      return CRYPT_BUFFER_OVERFLOW;
   }
   XMEMCPY(IV, cfb->IV, cfb->blocklen);
   *len = cfb->blocklen;

   return CRYPT_OK;
}

#endif

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
