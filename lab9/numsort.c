//Graham Greving
//ggreving
//Joe Rowley
//jrowley ucsc.edu

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <math.h>
#include "inssort.h"

#define ARRAY_SIZE 1000
char *progname = NULL;

int doublecmp (const void *this, const void *that) {
   double *thisdoub = (double*) this;
   double *thatdoub = (double*) that;
   return *thisdoub < *thatdoub ? -1 : *thisdoub > *thatdoub ? +1 : 0;
}

int main(int agrc, char **argv) {
   progname = basename (argv[0]);
   double array[ARRAY_SIZE];
   int count = 0;
   for (; ;count++) {
      if (count == ARRAY_SIZE) {
         //printf("Full Array, call inssort.\n");
         //if (rc != 0) {
         //array[count] = num;
         //}else printf("Invalid Input, call inssort\n");
         break;
      } 
      double num;
      int rc = scanf("%lg",&num);
      if (rc == EOF) {
         //printf("EOF, call inssort\n");
         break;
      } 
      if (rc != 0) {
         array[count] = num;
      } 
      else {
         //printf("Invalid Input, call inssort\n");
         return EXIT_FAILURE;
      }
   }
   int i = agrc; //get ride of warning of not using agrc
   i++;
   //qsort(array, count, sizeof (double), doublecmp);
   inssort(array, count, sizeof (double), doublecmp);
   for (int i = 0; i < count; i++) {
      printf("%20.15g\n",array[i]);
   }
}
