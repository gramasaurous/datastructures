// $Id: linkedlist.java,v 1.1 2012-10-18 13:19:38-07 - - $
//Graham Greving
//ggreving
//
import java.util.Iterator;
import java.util.Scanner;
import java.io.*;
import static java.lang.System.*;
import java.util.NoSuchElementException;

class linkedlist implements Iterable<pair> {

   private class node {
      pair item;
      node link;
   }
   private node head = null;
   
   public String get (String key) {
      node ptr = head;
      int cmp = 1;
      while (ptr != null) {
         cmp = ptr.item.key.compareTo(key);
         if (cmp == 0) {
            return ptr.item.value;
         }
         ptr = ptr.link;
      }  
      return null;
   }

   public String put (String key, String value) {
      node curr = head;
      node prev = null;
      int cmp = 1;
      while (curr != null) {
         cmp = curr.item.key.compareTo(key);
         if (cmp >= 0) break;
         prev = curr;
         curr = curr.link;
      }
      if (cmp != 0) {
         node tmp = new node();
         tmp.item = new pair(key, value);
         tmp.link = curr;
         if (prev == null) head = tmp;
                      else prev.link = tmp;
         return tmp.item.key;
      } else {
         curr.item.value = value;
         return curr.item.key;
      }
   }

   public String delete (String key) {
      node curr = head;
      node prev = null;
      int cmp = 1;
      while (curr != null) {
         cmp = curr.item.key.compareTo(key);
         if (cmp == 0) {
            String returnVal = curr.item.value;
            if (prev == null && curr.link == null) {
               head = null;
               return returnVal;
            } else {
               curr = curr.link;
               prev.link = curr;
               return returnVal;
            }
         }
         prev = curr;
         curr = curr.link;
      } return null;
   }
   
   public Iterator<pair> iterator () {
      return new itor ();
   }

   private class itor implements Iterator<pair> {
      private node nextnode = head;

      public boolean hasNext () {
         return nextnode != null;
      }

      public pair next () {
         if (! hasNext()) throw new NoSuchElementException ();
         pair result = nextnode.item;
         nextnode = nextnode.link;
         return result;
      }

      public void remove () {
         throw new UnsupportedOperationException ();
      }
   }
}
