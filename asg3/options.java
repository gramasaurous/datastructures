// $Id: options.java,v 1.1 2012-10-31 13:12:50-07 - - $
import java.io.*;
import static java.lang.System.*;

class options {
   boolean count_only = false;
   boolean dump_tree = false;
   boolean fold_cases = false;
   String[] filenames = null;
   int fnStart = 0;

   options (String[] args) {
      if (args.length == 0) {
         filenames = new String[1];
         filenames[0] = "-";
      }
      int i = 0;
      while(i < args.length && args[i].startsWith("-")
            && args[i].length() != 1) {
         String tmp = args[i];
         if (tmp.contains("c")){count_only = true; out.printf("C\n");}
         if (tmp.contains("d")){dump_tree = true; out.printf("D\n");}
         if (tmp.contains("f")){fold_cases = true; out.printf("F\n");}
         i++;
      }
      fnStart = i;
      filenames = new String[args.length - fnStart];
      int k = 0;
      for (int fni = fnStart; fni < args.length; ++fni) {
         filenames[k++] = args[fni];
      }
   }
}
