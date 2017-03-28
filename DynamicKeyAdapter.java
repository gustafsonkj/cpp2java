import java.awt.event.KeyAdapter;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import java.io.*;

public class DynamicKeyAdapter extends KeyAdapter
{
   public void keyReleased (KeyEvent ke)
   {
      try
      {
         FileWriter output = new FileWriter("Java2Cpp.csv");
         BufferedWriter writer = new BufferedWriter(output);
         writer.write("-1,KeyEvent,"+ke.getKeyChar());
         writer.close();
      }
      catch (IOException e)
      {
         
      }
   }
}

