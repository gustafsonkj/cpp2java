import javax.swing.*;
import java.awt.event.*;
import java.io.*;

public class DynamicItemListener implements ItemListener
{
   public void itemStateChanged(ItemEvent ie)	{
      
      Object src = ie.getSource();
      
      if (src instanceof DynamicJCheckBox)
         Cpp2Java.sendCommandThroughPipe("1,"+(DynamicJCheckBox)src.getID()+",itemStateChanged,"+ ie.getStateChange() + "~");
      else if (src instanceof DynamicJRadioButton)
         Cpp2Java.sendCommandThroughPipe("1,"+(DynamicJRadioButton)src.getID()+",itemStateChanged,"+ ie.getStateChange() + "~");
   }
}