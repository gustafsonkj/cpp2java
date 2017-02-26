import java.util.Vector;
import javax.swing.*;
import java.awt.*;

public class DynamicJPanel extends JPanel
{
   private Vector<String> commands;
   public void setCommand(String command)
   {
      commands.add(command);
   }
   public void paint(Graphics g)
   {
      super.paint(g);
      //switch(stuff in commands)
        // case "drawRect": g.drawRect...
         
   }
}