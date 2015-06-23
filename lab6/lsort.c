//Graham Greving
//ggreving

#include <libgen.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

//define standard input as input for fgets
//could be changed for a file for debugging purposes
#define INPUT stdin

char *progname = NULL;
int exit_status = EXIT_SUCCESS; // Assume successful completion.

//option type
struct options {
   bool debug;
};


//pseudo string
typedef char *cstring;

//pseudo reference (node pointer)
typedef struct node *node_ref;
struct node {
    cstring item;
    node_ref link;
};

//plumber function fixes leaks (memory leaks)
int plumber(node_ref listhead) {
   while (listhead != NULL) {
      node_ref old = listhead;
      listhead = listhead->link;
      free(old->item);
      free(old);
   }
   return EXIT_SUCCESS;
}

//printall function prints all values in the list
//if option d is passed, printall prints pointers
int printall(node_ref ptr, struct options *opts) {
   if (opts->debug == true) {
      for (node_ref curr = ptr; curr != NULL; curr = curr->link) {
         printf ("%p -> struct node {item= %s, link= %p}\n",
                     (void*) curr, curr->item, (void*) curr->link);
      }
      return EXIT_SUCCESS;
   } else {
      node_ref curr = ptr;
      while (curr != NULL) {
         printf("%s\n", curr->item);
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
   char buffer[72];
   int linenr;
   for (linenr = 1; ; ++linenr) {

      // Read a line of input and check to see if it ends with
      // a newline character.  Print a message if not.

      char *gotline = fgets (buffer, sizeof buffer, stdin);
      if (gotline == NULL) break;

      char *nlpos = strchr (buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }else {
         exit_status = EXIT_FAILURE;
         fprintf (stderr, "%s: %d: unterminated line: %s\n",
                  progname, linenr, buffer);
      }
      //create the new node
      node_ref new = malloc (sizeof(struct node));
      assert(new != NULL);
      new->item = strdup(buffer);
      
      node_ref prev = NULL;
      node_ref curr = head;
      //find insertion point
      while (curr != NULL) {
         int cmp = strcmp(curr->item, new->item);
         if (cmp > 0) break;
         prev = curr;
         curr = curr->link;
      }
      //do insertion
      new->link = curr;
      if (prev == NULL) head = new;
         else prev->link = new;
   }
   printall(head, &opts);
   plumber(head);
   return exit_status;
}

