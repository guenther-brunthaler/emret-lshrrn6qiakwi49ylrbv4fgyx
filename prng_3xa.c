#include <dim-sdbrke8ae851uitgzm4nv3ea2.h>
#include <rand-uhrltlhmrn3cke0bsezw006ys.h>
#include <assert.h>
#include <math.h>

typedef u32 (*arng)[55];

struct prng_state {
   arng k1, k2, k3;
   unsigned i;
};

static u32 gen_k1(arng a, unsigned n) {
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
   assert(n < 55);
   if ((n_minus_24= n + (55 - 24)) >= 55) n_minus_24-= 55;
   assert(n_minus_24 < 55);
   return (*a)[n]+= (*a)[n_minus_24] & m_minus_1;
}

static u32 gen_k3(struct prng_state *state) {
   unsigned i;
   u32 r= gen_k1(state->k1, i= state->i);
   r^= gen_k1(state->k2, i);
   r^= gen_k1(state->k3, i);
   if (++i >= 55) i= 0;
   state->i= i;
   return r;
}

static double generate_next(void *random_context) {
   double r;
   struct prng_state *state= random_context;
   r= ldexp(gen_k3(state), -32);
   return ldexp(r + gen_k3(state), -32);
}

static void seed_k(arng a, random_u32 rng, void *random_context) {
   u32 or= 0;
   unsigned n;
   for (n= DIM(*a); n--; ) or|= (*a)[n]= (*rng)(random_context);
   (*a)[0]|= ~or & 1; /* Make first element odd if all elements are even. */
}

struct preseed {
   random_u32 rng;
   void *random_context;
   struct prng_state *state;
};

static void preseed_k1(struct preseed *p, arng a1) {
   unsigned i;
   for (i= DIM(*a1); i--; ) {
      unsigned j;
      u32 r= 0;
      for (j= 4; j--; ) r= r << 8 | (*p->rng)(p->random_context) >> 32 - 8;
      (*a1)[i]= r;
   }
}
static char const *preseed_helper_cont(void *context) {
   struct preseed *pre= context;
   preseed_k1(pre, pre->state->k1);
   preseed_k1(pre, pre->state->k2);
   preseed_k1(pre, pre->state->k3);
   return 0;
}

static char const *preseed_helper(unsigned seed, struct prng_state *rctx) {
   struct preseed pre;
   pre.state= rctx;
   return prng_u32(
      seed, &pre.rng, &pre.random_context, preseed_helper_cont, &pre
   );
}

char const *prng_3xa(
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
