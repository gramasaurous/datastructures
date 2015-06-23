//Graham Greving
//ggreving
//

import java.util.Iterator;
import java.util.Scanner;
import java.io.*;
import static java.lang.System.*;

class keyvalue {
   
   public static linkedlist list = new linkedlist();
   
   public static void processInput(Scanner input) {
      //linkedlist list = new linkedlist();
      while(input.hasNext()) {
         String line = input.nextLine();
         line = line.trim();
         if (line.length() == 1 && line.startsWith("=")) {
            for (pair item : list) {
               out.printf ("%s = %s%n", item.key, item.value);
            }
         } else if (line.startsWith("=")) {
            String searchVal = line.substring(1);
            searchVal = searchVal.trim();
            int cmp = 1;
            for (pair item : list) {
               cmp = item.value.compareTo(searchVal);
               if (cmp == 0) {
                  out.printf ("%s = %s%n", item.key, item.value);
               }
            }
         } else if (line.startsWith("#")) {
            //out.println("COMMENT");
            continue;
            
         } else if (line.endsWith("=")) {
            int end = line.length() - 1;
            String value = line.substring(0, end);
            value = value.trim();
            String delete = list.delete(value);
            if (delete == null) {
               out.printf("%s: not found%n", value);
            } else {
               out.printf ("%s = %s%n", value, delete);
            }
            
         } else if (line.contains("=")) {
            String[] keyval = line.split("=");
            keyval[0] = keyval[0].trim();
            keyval[1] = keyval[1].trim();
            String returnval = list.put(keyval[0],keyval[1]);
            out.println(returnval);
            
         } else {
            boolean found = false;
            for (pair item : list) {
               if ((item.key).compareTo(line) == 0) {
                  out.printf("%s = %s%n", item.key, item.value);
                  found = true;
                  break;
               }
            }
            if (found == false) {
               out.printf("%s: not found%n", line);
            }
         }
      }
   }
   
   public static void main (String[] args) {
      //linkedlist list = new linkedlist();
      
      
      if (args.length == 0) {
         Scanner input = new Scanner(in);
         processInput(input);
         input.close();
      }
      for (int i = 0; i < args.length; i++) {
         if (args[i].equals("-")) {
            Scanner input = new Scanner(in);
            processInput(input);
            input.close();
         } else {
            try {
               String filename = args[i];
               Scanner input = new Scanner (new File (filename));
               processInput(input);
               input.close();
            }catch (IOException error) {
               messages.warn (error.getMessage());
            }
         }
      }
      ////////// delete these loops and replace with prog //////////
      //for (pair item : list) {
      //   out.printf ("%s = %s%n", item.key, item.value);
      //}
      //for (Iterator<pair> itor = list.iterator();
      //     itor.hasNext (); ) {
      //   pair item = itor.next ();
      //   out.printf ("%s = %s%n", item.key, item.value);
      //}
   }

}

