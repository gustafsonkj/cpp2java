
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class Cpp2Java extends JFrame { //One-JFrame setup
      private static Container contents;
      //private ArrayList<JComponent>();
   public Cpp2Java()
   {
      super("Cpp2Java");
		  contents	= getContentPane();
        setSize(720,540);
		setVisible(true);

   }
  public static void main(String args[]) {
    // monitor a single file
    Cpp2Java fwt = new Cpp2Java();
   fwt.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
   contents.add(new testPanel());
   //fwt.revalidate();
      
    TimerTask task = new FileWatcher( new File("text.txt") ) {
     JPanel test;
     FileReader fr;
     BufferedReader br;
     String line;
      protected void onChange( File file ) {
      
        // here we code the action on a change
        System.out.println( "File "+ file.getName() +" have change !" );
        fr = new FileReader(new File("text.txt"));
        br = new BufferedReader(fr);
        ArrayList<JComponent> comps = new ArrayList<JComponent>();
        while((line = br.readLine()) != null)
        {
            String[] command = line.split(",");
            switch(command[0])
            {
               case "removeAll":
               {
                  contents.removeAll();
               }
               case "instantiate":
               {
                  switch(command[1])
                  {
                     case "JPanel": comps[command[2]] = new JPanel();
                     break;
                     case "JLabel": comps[command[3]] = new JLabel(command[2]);
                     break;
                  }
               }
               case "add":
               {
                  // Command [1] is the JComponent you're adding TO
                  // Command [2] is the JComponent that you're adding
                  comps[command[1]].add(comps[command[2]]);
               }
            }
        }
      /*for each line in textFile:
         switch (line[0])
            case "instantiate":
               switch (line[1]
                  case "JPanel": ArrayListOfJComponents.add(new JPanel());
                  case "JLAbel:" ARrayListOf
            case "removeall":
               fwt.removeAll();
            case "add":
               ArrayLits[0].add(ArrayList[1]);
               */
        //contents.removeAll();
        contents.add(new testPanel());
        fwt.revalidate();
         fwt.repaint();
        /* Swap JPanel (one-JPanel setup)
        
        this.removeAll();
        this.add(new userJPanel());
        
        this.revalidate(); ???
        this.update(); ???
        
        
        */
      }
    };

    java.util.Timer timer = new java.util.Timer();
    // repeat the check every second
    timer.schedule( task , new Date(), 1 );
  }
}