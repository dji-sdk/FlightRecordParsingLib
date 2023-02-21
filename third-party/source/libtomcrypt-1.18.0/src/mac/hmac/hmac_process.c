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
  @file hmac_process.c
  HMAC support, process data, Tom St Denis/Dobes Vandermeer
*/

#ifdef LTC_HMAC

/**
  Process data through HMAC
  @param hmac    The hmac state
  @param in      The data to send through HMAC
  @param inlen   The length of the data to HMAC (octets)
  @return CRYPT_OK if successful
*/
int hmac_process(hmac_state *hmac, const unsigned char *in, unsigned long inlen)
{
    int err;
    LTC_ARGCHK(hmac != NULL);
    LTC_ARGCHK(in != NULL);
    if ((err = hash_is_valid(hmac->hash)) != CRYPT_OK) {
        return err;
    }
    return hash_descriptor[hmac->hash].process(&hmac->md, in, inlen);
}

#endif


/* ref:         HEAD -> master, tag: v1.18.0 */
/* git commit:  0676c9aec7299f5c398d96cbbb64f7e38f67d73f */
/* commit time: 2017-10-10 15:51:36 +0200 */
