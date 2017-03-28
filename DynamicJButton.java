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
      
      try
      {
         FileWriter output = new FileWriter("Java2Cpp.csv");
         BufferedWriter writer = new BufferedWriter(output);
        DynamicJButton temp = (DynamicJButton)ae.getSource();          
         writer.write("actionPerformed"+temp.getID());
         
      }
      
      catch(IOException e)
      {
      
      }

      
   }
 }
/*class DynamicActionListener implements ActionListener
{
   public void actionPerformed(ActionEvent ae)
   {   }
   
}*/