#include <with_malloc_buffer-9j76cc1vs6bi14ip2ii9f1yla.h>
#include <stdlib.h>
#include <assert.h>

char const *with_malloc_buffer(
      void *buffer_ref /* Actually a "void **". Required. */
   ,  size_t *size_ref /* Optional. */
   ,  size_t initial_size
   ,  resource_user body, void *context
) {
   char const *status;
   assert(buffer_ref);
   {
      void *buffer;
      if (initial_size) {
         if (!(buffer= malloc(initial_size))) {
            return "Memory allocation failure!";
         }
      } else {
         buffer= 0;
      }
      *(void **)buffer_ref= buffer;
      if (size_ref) *size_ref= initial_size;
   }
   status= (*body)(context);
   free(*(void **)buffer_ref);
   return status;
}
