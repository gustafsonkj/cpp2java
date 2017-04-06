import javax.swing.*;
import java.awt.event.*;
import java.io.*;

public class DynamicJButton extends JButton implements ActionListener
{
  private int id;
   
   public DynamicJButton(int ID){
      id = ID;
      //addActionListener(this);
   }
   
   public int getID(){
      return id;
   }
   
   public void addActionListener()
   {
        addActionListener(this);
   }
   
   public void actionPerformed(ActionEvent ae)
   {
      

      DynamicJButton temp = (DynamicJButton)ae.getSource();   
         Cpp2Java.sendCommandThroughPipe(temp.getID()+"actionPerformed,");
         
 }
 }
/*class DynamicActionListener implements ActionListener
{
   public void actionPerformed(ActionEvent ae)
   {   }
   
}*/