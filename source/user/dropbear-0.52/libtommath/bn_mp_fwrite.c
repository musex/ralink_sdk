#include <tommath.h>
#ifdef BN_MP_FWRITE_C
/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is a library that provides multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library was designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://math.libtomcrypt.com
 */

int mp_fwrite(mp_int *a, int radix, FILE *stream)
{
   char *buf;
   int err, len, x;
   
   if ((err = mp_radix_size(a, radix, &len)) != MP_OKAY) {
      return err;
   }

   buf = OPT_CAST(char) XMALLOC (len);
   if (buf == NULL) {
      return MP_MEM;
   }
   
   if ((err = mp_toradix(a, buf, radix)) != MP_OKAY) {
      XFREE (buf);
      return err;
   }
   
   for (x = 0; x < len; x++) {
       if (fputc(buf[x], stream) == EOF) {
          XFREE (buf);
          return MP_VAL;
       }
   }
   
   XFREE (buf);
   return MP_OKAY;
}

#endif

/* $Source: /home/cvsroot/RT288x_SDK/source/user/dropbear-0.52/libtommath/bn_mp_fwrite.c,v $ */
/* $Revision: 1.1 $ */
/* $Date: 2010-07-02 06:29:23 $ */