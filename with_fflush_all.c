#include <with_fflush_all-0p13ursnxj34l8jy5bmjp4m70.h>
#include <stdio.h>

char const *with_fflush_all(resource_user body, void *context) {
   char const *error= (*body)(context);
   if (fflush(0) && !error) error= "Error writing remaining output.";
   return error;
}
