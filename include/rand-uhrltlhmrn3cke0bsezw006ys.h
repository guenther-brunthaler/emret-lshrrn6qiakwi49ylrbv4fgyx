#ifndef HEADER_UHRLTLHMRN3CKE0BSEZW006YS_INCLUDED
#define HEADER_UHRLTLHMRN3CKE0BSEZW006YS_INCLUDED
#ifdef __cplusplus__
extern "C" {
#endif

#include <ruser-qv7m1cmnh6dr7cl740wg6ss3w.h>
#include <stddef.h>
#include <stdio.h>
#include <limits.h>

#if USHRT_MAX >= 0xffffffff
   typedef unsigned short u32;
#elif UINT_MAX >= 0xffffffff
   typedef unsigned int u32;
#elif ULONG_MAX >= 0xffffffff
   typedef unsigned long u32;
#else
   #error "ULONG_MAX does not comply with the ANSI C standard!"
#endif

typedef u32 (*random_u32)(void *random_context);
typedef double (*random_double)(void *random_context);

/* Call body with a seeded LCRNG. */
char const *prng_u32(
      unsigned seed /* Random seed. */
   ,  random_u32 *rgen /* Where to put pointer to generator function. */
   ,  void **rgen_context /* Where to put its context. */
   ,  resource_user body, void *context
);

/* Call body with seeded ISAAC prng.*/
char const *prng_isaac(
      unsigned seed /* Random seed. */
   ,  random_double *rgen /* Where to put pointer to generator function. */
   ,  void **rgen_context /* Where to put its context. */
   ,  resource_user body, void *context
);

/* Call body with two seeded Knuth's Additive RNGs, all XORed together.*/
char const *prng_2xa(
      unsigned seed /* Random seed. */
   ,  random_double *rgen /* Where to put pointer to generator function. */
   ,  void **rgen_context /* Where to put its context. */
   ,  resource_user body, void *context
);


#ifdef __cplusplus__
}
#endif
#endif /* !HEADER_UHRLTLHMRN3CKE0BSEZW006YS_INCLUDED */
