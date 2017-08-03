#include <rand-uhrltlhmrn3cke0bsezw006ys.h>
#include <assert.h>

struct prng_state {
   u32 seed;
};

static u32 generate_next(void *random_context) {
   struct prng_state *state= random_context;
   u32 const a= 1664525;
   u32 const c= 1013904223;
   u32 const m= 0xffffffff;
   return state->seed= state->seed * a + c & m;
}

char const *prng_u32(
      unsigned seed /* Random seed. */
   ,  random_u32 *rgen /* Where to put pointer to generator function. */
   ,  void **rgen_context /* Where to put its context. */
   ,  resource_user body, void *context
) {
   unsigned warmup_rounds= 5;
   struct prng_state rctx;
   unsigned n;
   rctx.seed= (u32)seed;
   while (warmup_rounds--) (void)generate_next(&rctx);
   assert(rgen); *rgen= &generate_next;
   assert(rgen_context); *rgen_context= &rctx;
   (*body)(context);
}
