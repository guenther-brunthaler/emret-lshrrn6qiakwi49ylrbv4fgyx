#include <with_FILE-ctm26us35u661x9z4pyf8z0e1.h>
#include <stdio.h>
#include <assert.h>

char const *with_FILE(
      FILE **fh_ref, char const *fname, char const *modes
   ,  resource_user body, void *context
) {
   char const *error;
   assert(fh_ref);
   if (!(*fh_ref= fopen(fname, modes))) return "Could not open file!";
   error= (*body)(context);
   if (fclose(*fh_ref) && !error) {
      error= "Error writing buffered output data!";
   }
   return error;
}
