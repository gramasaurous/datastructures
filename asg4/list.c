//Graham Greving
//ggreving

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "list.h"

static char *list_tag = "struct list";
static char *listnode_tag = "struct listnode";

typedef struct listnode *listnode_ref;

struct list {
   //
   // INVARIANT:  Both head and last are NULL or neither are NULL.
   // If neither are null, then following listnode next links from
   // head will get to last, and prev links from last gets to head.
   //
   char *tag;
   listnode_ref head;
   listnode_ref curr;
   listnode_ref last;
};

struct listnode {
   char *tag;
   char *line;
   listnode_ref prev;
   listnode_ref next;
};

void debugdump_list (list_ref list) {
   listnode_ref itor = NULL;
   assert (is_list (list));
   fflush (NULL);
   fprintf (stderr,
            "\n[%p]->struct list {tag=[%p]->[%s];"
            " head=[%p]; curr=[%p]; last=[%p]; }\n",
            list, list->tag, list->tag,
            list->head, list->curr, list->last);
   for (itor = list->head; itor != NULL; itor = itor->next) {
      fprintf (stderr,
               "[%p]->struct listnode {tag=[%p]->[%s];"
               " line=[%p]=[%s]; prev=[%p]; next=[%p]; }\n",
               itor, itor->tag, itor->tag, itor->line, itor->line,
               itor->prev, itor->next);
   }
   fflush (NULL);
}


list_ref new_list (void) {
   list_ref list = malloc (sizeof (struct list));
   assert (list != NULL);
   list->tag = list_tag;
   list->head = NULL;
   list->curr = NULL;
   list->last = NULL;
   return list;
}

void free_list (list_ref list) {
   assert (is_list (list));
   assert (empty_list (list));
   STUBPRINTF ("list=[%p]\n", list);
}

bool setmove_list (list_ref list, list_move move) {
   assert (is_list (list));
   switch (move) {
      case MOVE_HEAD:
           list->curr = list->head;
           break;
           if (list->curr == list->head) return false;
           list->curr = list->curr->prev;
           break;
      case MOVE_NEXT:
           if (list->curr == list->last) return false;
           list->curr = list->curr->next;
           break;
      case MOVE_LAST:
           list->curr = list->last;
           break;
      default: return false;
   }
   return true;
}

char *viewcurr_list (list_ref list) {
   assert (is_list (list));
   //if (list->curr == list->head) return NULL;
   return list->curr->line;
}

void insert_list (list_ref list, char *line) {
   assert (is_list (list));
   listnode_ref new = malloc(sizeof (struct listnode));
   assert(new != NULL);
   new->line = strdup(line);
   new->tag = listnode_tag;
   
   //case: empty
   //    set up new as head
   //else:
   //    insert new after curr, set new to curr
   
   if (empty_list(list)) {
      list->curr = list->head = list->last = new;
   } else if (list->last == list->curr) {
      list->curr->next = new;
      new->prev = list->curr;
      list->last = new;
      new->next = NULL;
   } else {
      new->next = list->curr->next;
      list->curr->next->prev = new;
      list->curr->next = new;
      new->prev = list->curr;
   }
   list->curr = new;
}

void delete_list (list_ref list) {
   assert (is_list (list));
   assert (! empty_list (list));
   if (list->curr == list->last) {
      printf("curr == last\n");
      list->last = list->curr->prev;
      list->curr = list->last;
   } else if (list->curr == list->head) {
      printf("curr == head\n");
      list->head = list->curr->next;
      list->curr = list->head;
   } else {
      printf("curr in the middle\n");
      list->curr->next->prev = list->curr->prev;
      list->curr->prev->next = list->curr->next;
   }
}

bool empty_list (list_ref list) {
   assert (is_list (list));
   return list->head == NULL;
}

bool is_list (list_ref list) {
   return list != NULL && list->tag == list_tag;
}

