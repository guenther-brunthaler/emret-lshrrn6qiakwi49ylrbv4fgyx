#ifndef HEADER_9J76CC1VS6BI14IP2II9F1YLA_INCLUDED
#define HEADER_9J76CC1VS6BI14IP2II9F1YLA_INCLUDED
#ifdef __cplusplus__
extern "C" {
#endif

#include <ruser-qv7m1cmnh6dr7cl740wg6ss3w.h>
#include <stddef.h>

/* Allocate a buffer with an initial size (may be 0), call <body> while it is
 * allocated, then free the buffer. */
char const *with_malloc_buffer(
      void *buffer_ref /* Actually a "void **". Required. */
   ,  size_t *size_ref /* Optional. */
   ,  size_t initial_size
   ,  resource_user body, void *context
);

#ifdef __cplusplus__
}
#endif
#endif /* !HEADER_9J76CC1VS6BI14IP2II9F1YLA_INCLUDED */
