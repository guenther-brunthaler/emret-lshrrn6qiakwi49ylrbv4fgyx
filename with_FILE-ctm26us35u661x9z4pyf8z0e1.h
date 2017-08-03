#ifndef HEADER_CTM26US35U661X9Z4PYF8Z0E1_INCLUDED
#define HEADER_CTM26US35U661X9Z4PYF8Z0E1_INCLUDED
#ifdef __cplusplus__
extern "C" {
#endif

#include <ruser-qv7m1cmnh6dr7cl740wg6ss3w.h>
#include <stdio.h>

/* Open the file, call <body> while it is open, then close the file. */
char const *with_FILE(
      FILE **fh_ref, char const *fname, char const *modes
   ,  resource_user body, void *context
);

#ifdef __cplusplus__
}
#endif
#endif /* !HEADER_CTM26US35U661X9Z4PYF8Z0E1_INCLUDED */
