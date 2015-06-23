//Graham Greving
//ggreving

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugf.h"
#include "list.h"

bool want_echo = true;

void badline (int stdincount, char *stdinline) {
   fflush (NULL);
   fprintf (stderr, "Bad input line %d: %s\n", stdincount, stdinline);
   fflush (NULL);
}

//
//input functions
//.
void printcurr(list_ref list){
   printf("Curr: %s\n", viewcurr_list(list));
}
//$
void curr_to_last(list_ref list){
   if (setmove_list(list, MOVE_LAST)) printcurr(list);
   else printf("invalid op\n");
}
//*
void printall(list_ref list){
   if (empty_list(list)) return;
   if (!setmove_list(list, MOVE_HEAD)) return;
   while (true){
      printf("%s\n", viewcurr_list(list));
      if(!setmove_list(list, MOVE_NEXT)) return;
   }
}
//0
void curr_to_head(list_ref list){
   if (setmove_list(list, MOVE_HEAD)) printcurr(list);
   else printf("invalid op\n");
}
//<
void curr_to_prev(list_ref list){
   if (setmove_list(list, MOVE_PREV)) printcurr(list);
   else printf("invalid op\n");
}
//>
void curr_to_next(list_ref list){
   if (setmove_list(list, MOVE_NEXT)) printcurr(list);
   else printf("invalid op\n");
}
//a
void insert_after(list_ref list, char *input) {
   insert_list(list, input);
   printf("Inserted: %s\n", viewcurr_list(list));
}
//d
void delete_curr(list_ref list){
   delete_list(list);
}
//i
//void insert_before(list_ref list, char *input){}
//rfilename
//void read_and_insert(list_ref list){}
//wfilename
//void write_to_file(list_ref list, char *filename){}


void editfile (list_ref list) {
   char stdinline[1024];
   int stdincount = 0;
   for(;; ++stdincount) {
      printf ("%s: ", Exec_Name);
      char *linepos = fgets (stdinline, sizeof stdinline, stdin);
      if (linepos == NULL) break;
      if (want_echo) printf ("%s", stdinline);
      linepos = strchr (stdinline, '\n');
      if (linepos == NULL || stdinline[0] == '\0') {
         badline (stdincount, stdinline);
      } else {
         *linepos = '\0';
         switch (stdinline[0]) {
            case '#': printf("comment\n"); break;
            case '$': curr_to_last(list); break;
            case '*': printall(list); break;
            case '.': printcurr(list); break;
            case '0': curr_to_head(list); break;
            case '<': curr_to_prev(list); break;
            case '>': curr_to_next(list); break;
            case '@': debugdump_list (list); break;
            case 'a': insert_after (list, &stdinline[1]); break;
            case 'd': delete_curr(list); break;
            //case 'i': insert_before(list, &stdinline[1]); break;
            //case 'r': read_and_insert(list); break;
            //case 'w': write_to_file(list, &stdinline[1]); break;
            default : badline (stdincount, stdinline);
         }
      }
   }
}


void usage_exit() {
   fflush (NULL);
   fprintf (stderr, "Usage: %s filename\n", Exec_Name);
   fflush (NULL);
   exit (EXIT_FAILURE);
}

int main (int argc, char **argv) {
   Exec_Name = basename (argv[0]);
   if (argc != 2) usage_exit();
   want_echo = ! (isatty (fileno (stdin)) && isatty (fileno (stdout)));
   list_ref list = new_list();
   editfile (list);
   free_list (list); list = NULL;
   return Exit_Status;
}
