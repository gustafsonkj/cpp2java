import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.*;

class DynamicMouseListener extends MouseAdapter
{
   public void mouseClicked(MouseEvent me)
   {
      Cpp2Java.sendCommandThroughPipe("-1,MouseEvent,"+me.getX()+","+me.getY());
   }
   public void mousePressed(MouseEvent me)
   {
      Cpp2Java.sendCommandThroughPipe("-1,MouseEvent,"+me.getX()+","+me.getY());
   }
}