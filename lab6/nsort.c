//Graham Greving
//ggreving

#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

char *progname = NULL;          // Name of the program being run.
int exit_status = EXIT_SUCCESS; // Assume successful completion.

//options type
struct options {
   bool debug;
};
//pseudo reference (node pointer)
typedef struct node *node_ref;
struct node {
    double item;
    node_ref link;
};

//plumber function fixes leaks (memory leaks)
int plumber(node_ref listhead) {
   while (listhead != NULL) {
      node_ref old = listhead;
      listhead = listhead->link;
      free(old);
   }
   return EXIT_SUCCESS;
}

//printall function prints all values in the list
//if option d is passed, printall prints pointers
int printall(node_ref ptr, struct options *opts) {
   if (opts->debug == true) {
      for (node_ref curr = ptr; curr != NULL; curr = curr->link) {
         printf ("%p -> struct node {item= %.15g, link= %p}\n",
                     (void*) curr, curr->item, (void*) curr->link);
      }
      return EXIT_SUCCESS;
   } else {
      //print debug
      node_ref curr = ptr;
      while (curr != NULL) {
         printf("%24.15g\n", curr->item);
         curr = curr->link;
      }
      return EXIT_SUCCESS;
   }
}
//scan_options function takes in an options struct, as well as 
//the program arguments, and determines whether the available 
//options have been passed.
void scan_options (int argc, char **argv, struct options *opts) {
   opts->debug = false;
   
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "d");
      if (opt == EOF) break;
      switch (opt) {
         case 'd':
            opts->debug = true;
            break;
         default : 
            fflush (NULL);
            fprintf (stderr, "%s: -%c: invalid option\n",
                     progname, optopt);
            fflush (NULL);
            exit_status = EXIT_FAILURE;
       }
   }
}

int main (int argc, char **argv) {

   progname = basename (argv[0]);
   struct options opts;
   scan_options (argc, argv, &opts);
   if (exit_status == EXIT_FAILURE) return exit_status;
   
   node_ref head = NULL;
   while (1) {
      double num;
      int rc = scanf("%lg", &num);
      if (rc == EOF) {
         //printf("End of File\n");
         printall(head, &opts);
         break;
      } if (rc !=0 ) {
         //create the new node
         node_ref new = malloc (sizeof(struct node));
         assert(new!=NULL);
         new->item = num;
         
         node_ref prev = NULL;
         node_ref curr = head;
         //find insertion point
         while (curr != NULL) {
            if (curr->item > new->item) break;
            prev = curr;
            curr = curr->link;
         }
         //do insertion
         new->link = curr;
         if (prev == NULL) head = new;
            else prev->link = new;
      } else {
         //scanf did not recieve a double
         fprintf(stderr, "%s: invalid input\n", progname);
         exit_status = EXIT_FAILURE;
         return exit_status;
      }
   }
   plumber(head);
   return exit_status;
}


