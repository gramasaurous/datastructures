// $Id: malloc.c,v 1.1 2012-11-06 09:27:47-08 - - $

#include <stdio.h>
#include <stdlib.h>

typedef struct node *node_ref;
struct node {
   int value;
   node_ref link;
};

int main (int argc, char **argv) {
   node_ref ptr = malloc (sizeof (struct node));
   ptr = malloc (sizeof (struct node));
   ptr->value = 6;
   ptr->link = NULL;
   printf ("%p-> {%d, %p}\n", ptr, ptr->value, ptr->link);
   free (ptr);
   return EXIT_SUCCESS;
}
