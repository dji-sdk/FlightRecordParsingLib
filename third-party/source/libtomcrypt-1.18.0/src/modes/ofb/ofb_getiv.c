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
   @file ofb_getiv.c
   OFB implementation, get IV, Tom St Denis
*/

#ifdef LTC_OFB_MODE

/**
   Get the current initialization vector
   @param IV   [out] The destination of the initialization vector
   @param len  [in/out]  The max size and resulting size of the initialization vector
   @param ofb  The OFB state
   @return CRYPT_OK if successful
*/
int ofb_getiv(unsigned char *IV, unsigned long *len, symmetric_OFB *ofb)
{
   LTC_ARGCHK(IV  != NULL);
   LTC_ARGCHK(len != NULL);
   LTC_ARGCHK(ofb != NULL);
   if ((unsigned long)ofb->blocklen > *len) {
      *len = ofb->blocklen;
      return CRYPT_BUFFER_OVERFLOW;
   }
   XMEMCPY(IV, ofb->IV, ofb->blocklen);
   *len = ofb->blocklen;

   return CRYPT_OK;
}

#endif

/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
