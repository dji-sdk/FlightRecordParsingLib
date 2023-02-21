/* tests the montgomery routines */
#include <tommath.h>

int main(void)
{
   mp_int modulus, R, p, pp;
   mp_digit mp;
   long x, y;

   srand(time(NULL));
   mp_init_multi(&modulus, &R, &p, &pp, NULL);

   /* loop through various sizes */
   for (x = 4; x < 256; x++) {
       printf("DIGITS == %3ld...", x); fflush(stdout);
       
       /* make up the odd modulus */
       mp_rand(&modulus, x);
       modulus.dp[0] |= 1;
       
       /* now find the R value */
       mp_montgomery_calc_normalization(&R, &modulus);
       mp_montgomery_setup(&modulus, &mp);
       
       /* now run through a bunch tests */
       for (y = 0; y < 1000; y++) {
           mp_rand(&p, x/2);        /* p = random */
           mp_mul(&p, &R, &pp);     /* pp = R * p */
           mp_montgomery_reduce(&pp, &modulus, mp);
           
           /* should be equal to p */
           if (mp_cmp(&pp, &p) != MP_EQ) {
              printf("FAILURE!\n");
              exit(-1);
           }
       }
       printf("PASSED\n");
    }
    
    return 0;
}






/* ref:         HEAD -> master, tag: v1.0.1 */
/* git commit:  5953f62e42b24af93748b1ee5e1d062e242c2546 */
/* commit time: 2017-08-29 22:27:36 +0200 */
