//Graham Greving
//ggreving
//Joe Rowley
//jrowley ucsc.edu
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>
#include "inssort.h"

void inssort (void *base, size_t nelem, size_t size,
 int (*compar) (const void *, const void *)){
   for (size_t sorted = 1; sorted < nelem; ++sorted) {
      size_t slot = sorted;
      //elem_t = array[slot];
      void *copy = malloc(size);
      memcpy(copy, (char *)(base + slot * size), size);
      for (; slot > 0; --slot) {
         //int cmp = copy.compareTo (array[slot-1]);
         void *prev = base + ((slot-1) * size);
         int cmp = (*compar)(copy, prev);
         if (cmp > 0) break;
         //array[slot] = array[slot-1];
         memcpy((base + slot * size), prev, size);
      }
      //array[slot] = copy;
      memcpy((base + slot * size), copy, size);
      free(copy);
   }
}

