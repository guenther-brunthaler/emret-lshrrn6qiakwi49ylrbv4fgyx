#ifndef HEADER_6P7CQKA4JP2G26PKN2F0PYLEU_INCLUDED
#define HEADER_6P7CQKA4JP2G26PKN2F0PYLEU_INCLUDED
#ifdef __cplusplus__
extern "C" {
#endif

#include <stddef.h>
#include <stdio.h>

struct append_rest_of_file_vars {
   FILE *fh; /* An open file. */
   /* *(void **)buffer_ref must be null if *size_ref == 0. */
   void *buffer_ref; /* A void **: Address of buffer pointer variable. */
   size_t *size_ref; /* Address of variable for actually used buffer bytes. */
};

/* Append the unread rest of an open file to a buffer, enlarging it as
 * necessary. */
char const *append_rest_of_file(void *append_rest_of_file_vars);

#ifdef __cplusplus__
}
#endif
#endif /* !HEADER_6P7CQKA4JP2G26PKN2F0PYLEU_INCLUDED */
