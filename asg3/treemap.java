// $Id: treemap.java,v 1.1 2012-10-31 13:12:50-07 - - $

import java.io.*;
import static java.lang.System.*;

class treemap <key_t extends Comparable<key_t>, value_t> {

   private class bstree {
      key_t key;
      value_t value;
      bstree left;
      bstree right;
   }
   private bstree root = null;

   public value_t put (key_t key, value_t value) {
      bstree curr = root;
      while(curr != null) {
         int cmp = curr.key.compareTo(key);
         if (cmp == 1){
            value_t temp = curr.value;
            curr.value = value;
            return temp;
         } if (cmp > 0) curr = curr.right;
            else curr = curr.left;
      }
      return null;
   }

   public value_t get (key_t key) { 
      //standard binary search, if key is found return value
      //if not found return null
      bstree curr = root;
      while(curr != null) {
         int cmp = curr.key.compareTo(key);
         if (cmp == 1) return curr.value;
         if (cmp > 0) curr = curr.right;
            else curr = curr.left;
      }
      return null;
   }

   public value_t remove (key_t key) {
      throw new UnsupportedOperationException ();
   }

   public void visit_all (visitor <key_t, value_t> visitor_fn) {
      visit_all_inorder (root, visitor_fn);
   }

   private void visit_all_inorder (bstree tree,
                  visitor <key_t, value_t> visitor_fn) {
      visitor_fn.visit (tree.key, tree.value);
      throw new UnsupportedOperationException ();
   }

   public void debug_dump () {
      debug_dump_inorder (root, 0);
   }

   private void debug_dump_inorder (bstree tree, int depth) {
      if (tree == null) return;
      debug_dump_inorder (tree.left, depth + 1);
      out.printf ("%*s%d: %s => %s%n",
                  depth * 3, "", depth, tree.key, tree.value);
      debug_dump_inorder (tree.right, depth + 1);
   }

}
