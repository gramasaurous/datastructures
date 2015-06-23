//Graham Greving
//ggreving
//Joe Rowley
//jrowley ucsc.edu

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <math.h>
#include <string.h>
#include "inssort.h"

#define MAX_LINE_LEN 4096
#define BUFFER_SIZE 1000
char *progname = NULL;

int strstrcmp (const void *this, const void *that) {
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp (*thisstr, *thatstr);
}

int main(int argc, char **argv) {
   progname = basename (argv[0]);
   int count = 0;
   char line[MAX_LINE_LEN]; // line got using fgets
   char **buffer; 
   buffer = (char**)malloc(sizeof(char*) * BUFFER_SIZE); 
   count = 0; // initilize count. 
   while(fgets(line,MAX_LINE_LEN,stdin)) {
        if (feof(stdin)){ //EOF
            //printf("EOF, call inssort\n");
            break;
        }
        buffer[count] = strdup(line);
        count++;
        if (count == BUFFER_SIZE) {
            //printf("Full Array, call inssort.\n");
            break;
        }
   }
   int i = argc;
   i++; // getting ride of not using agrc warning - lame
   //qsort(buffer, count, sizeof (buffer[0]), strstrcmp);
   inssort(buffer, count, sizeof(buffer[0]), strstrcmp);
   for (int i = 0; i < count ; i++) {
      printf("%s", buffer[i]);
   }
   for(count=0;count<BUFFER_SIZE;count++) {
     free(buffer[count]);
   }
   free(buffer);
}
