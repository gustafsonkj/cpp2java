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
<<<<<<< HEAD
         writer.write(temp.getID()+"actionPerformed,");
=======
         writer.write(temp.getID()+",ActionPerformed");
>>>>>>> c6fb68e06760728811f63459ce349203e6a80548
         
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