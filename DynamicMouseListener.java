import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;

class DynamicMouseListener extends MouseAdapter
{

   public void mouseClicked(MouseEvent me)
   {
      try{
          FileWriter output = new FileWriter("Java2Cpp.csv");
          BufferedWriter writer = new BufferedWriter(output);
          writer.write("-1,MouseEvent,"+me.getX()+","+me.getY());
          writer.close();
      }
        catch(IOException e) {} 
   }
}