#include <dim-sdbrke8ae851uitgzm4nv3ea2.h>
#include <rand-uhrltlhmrn3cke0bsezw006ys.h>
#include <assert.h>
#include <math.h>
#include <float.h>

typedef u32 arng[55];

struct prng_state {
   arng k1, k2;
   unsigned i;
};

static u32 gen_k1(arng *a, unsigned n) {
   /* Additive Random Number Generator:
    *
    * rnd[n]:= (rnd[n - 24] + rnd[n - 55]) mod m
    *
    * where
    * n >= 55
    * m is even
    * rnd[0 .. 54] are arbitrary seed integers, not all of them even
    *
    * The generated sequence will have a period of at least 2 ^ 55 - 1. */
   unsigned const m_minus_1= 0xffffffff;
   unsigned n_minus_24;
   assert(DIM(*a) == 55);
   assert(n < (unsigned)DIM(*a));
   if (
      (n_minus_24= n + ((unsigned)DIM(*a) - 24))
      >= (unsigned)DIM(*a)
   ) {
      n_minus_24-= (unsigned)DIM(*a);
   }
   assert(n_minus_24 < (unsigned)DIM(*a));
   return (*a)[n]= (*a)[n] + (*a)[n_minus_24] & m_minus_1;
}

static u32 gen_k2(struct prng_state *state) {
   unsigned i;
   u32 r= gen_k1(&state->k1, i= state->i);
   r^= gen_k1(&state->k2, i);
   if (++i == (unsigned)DIM(state->k1)) i= 0;
   assert(i < (unsigned)DIM(state->k1));
   state->i= i;
   return r;
}

static double generate_next(void *random_context) {
   double r;
   struct prng_state *state= random_context;
   #ifdef LESS_PORTABLE_BUT_FASTER_FOR_INFERIOR_OPTIMIZERS
      /* GCC 6.3.0 bug? Without the second cast, a -Wbad-function-cast
       * gcc-warnings will be triggered. While the first cast may be necessary
       * on platforms where it results in a loss of precision, casting a
       * function to its own return type seems pointless to me. However,
       * keeping the casts for now to make gcc happy. They certainly do not
       * hurt. */
      r= ldexp((double)(u32)gen_k2(state), -32);
      return ldexp(r + gen_k2(state), -32);
   #else
      /* This will become horribly inefficient unless the C optimizer is able
       * to precompute all the following "const"s ahead at compile time. At
       * least GCC 6.3.0 *is* capable of doing so with -O2 or better. */
      double const max_mantissa
         = pow((double)FLT_RADIX, (double)DBL_MANT_DIG) - 1.0
      ;
      double const mantissa_bits= log(max_mantissa) / log(2.0);
      double const mantissa_fullbits_dbl= floor(mantissa_bits);
      unsigned const mantissa_fullbits= (unsigned)mantissa_fullbits_dbl;
      #define MINIMUM(x, y) x <= y ? x : y
      unsigned const used_u32_bits= MINIMUM(mantissa_fullbits, 32u);
      #undef MINIMUM
      int const lshift= -(int)used_u32_bits;
      #define BITMASK(one, bits) ((one << bits - 1) - one << 1) + one
      u32 const bitmask= (u32)BITMASK((u32)1, used_u32_bits);
      #undef BITMASK
      r= ldexp((double)(gen_k2(state) & bitmask), lshift);
      return ldexp(r + (gen_k2(state) & bitmask), lshift);
   #endif
}

struct preseed {
   random_u32 rng;
   void *random_context;
   struct prng_state *state;
};

static void preseed_k1(struct preseed *p, arng *a1) {
   unsigned i;
   u32 or= 0;
   for (i= DIM(*a1); i--; ) {
      unsigned j;
      u32 r= 0;
      for (j= 4; j--; ) r= r << 8 | (*p->rng)(p->random_context) >> 32 - 8;
      or|= (*a1)[i]= r;
   }
   (*a1)[0]|= ~or & 1; /* Make first element odd if all elements are even. */
}
static char const *preseed_helper_cont(void *context) {
   struct preseed *pre= context;
   pre->state->i= 0;
   preseed_k1(pre, &pre->state->k1);
   preseed_k1(pre, &pre->state->k2);
   return 0;
}

static char const *preseed_helper(unsigned seed, struct prng_state *rctx) {
   struct preseed pre;
   pre.state= rctx;
   return prng_u32(
      seed, &pre.rng, &pre.random_context, preseed_helper_cont, &pre
   );
}

char const *prng_2xa(
      unsigned seed /* Random seed. */
   ,  random_double *rgen /* Where to put pointer to generator function. */
   ,  void **rgen_context /* Where to put its context. */
   ,  resource_user body, void *context
) {
   struct prng_state rctx;
   char const *error;
   if (error= preseed_helper(seed, &rctx)) return error;
   assert(rgen); *rgen= &generate_next;
   assert(rgen_context); *rgen_context= &rctx;
   return (*body)(context);
}
