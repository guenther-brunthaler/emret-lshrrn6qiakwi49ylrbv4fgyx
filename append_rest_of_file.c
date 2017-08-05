#include <append_rest_of_file-6p7cqka4jp2g26pkn2f0pyleu.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char const *append_rest_of_file(void *context) {
   size_t const initial_bufsz_inc= 8000;
   size_t const max_bufsz_inc= 8000000;
   struct append_rest_of_file_vars *v= context;
   char *buffer= *(void **)v->buffer_ref;
   size_t allocated, used;
   FILE *fh= v->fh;
   size_t bufsz_inc= initial_bufsz_inc;
   allocated= used= *v->size_ref;
   for (;;) {
      size_t read;
      if (allocated == used) {
         size_t new_size;
         void *new_buf= realloc(
            buffer, new_size= allocated + bufsz_inc
         ); if (!new_buf) return "Could not enlarge a growing buffer!";
         *(void **)v->buffer_ref= buffer= new_buf;
         *v->size_ref= allocated= new_size;
         if (bufsz_inc < max_bufsz_inc) {
            if ((bufsz_inc+= bufsz_inc) > max_bufsz_inc) {
               bufsz_inc= max_bufsz_inc;
            }
         }
      }
      assert(allocated > used);
      if (
         !(read= fread(buffer + used, sizeof *buffer, allocated - used, fh))
      ) {
         if (ferror(fh)) return "File read error!";
         if (feof(fh)) break;
      }
      used+= read;
   }
   if (allocated != used) {
      assert(allocated > used);
      if (!(buffer= realloc(buffer, used))) {
         return "Could not shrink a buffer!";
      }
      *(void **)v->buffer_ref= buffer;
      *v->size_ref= used;
   }
   return 0;
}
