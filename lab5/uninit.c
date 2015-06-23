// $Id: uninit.c,v 1.1 2012-11-06 09:09:50-08 - - $

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   int foo;
   printf ("%d\n", foo);
   int *pointer;
   printf ("%d\n", *pointer);
}
