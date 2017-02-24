import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class Cpp2Java extends JFrame { //One-JFrame setup
    private static Container contents;
    //private ArrayList<JComponent>();
    public Cpp2Java() {
        super("Cpp2Java");
        contents = getContentPane();
        contents.setLayout(new GridLayout(2,2));
        setSize(720, 540);
        setVisible(true);

    }
    public static void main(String args[]) {
        // monitor a single file
        Cpp2Java frame = new Cpp2Java();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        //frame.revalidate();

        TimerTask task = new FileWatcher(new File("text.csv")) {
            JPanel test;
            FileReader fr;
            BufferedReader br;
            String fileLine;
            protected void onChange(File file) {
               ArrayList < JComponent > comps = new ArrayList < JComponent > (64);
                // here we code the action on a change
                System.out.println("File " + file.getName() + " have change !");
                try {
                    fr = new FileReader(new File("text.csv"));
                } catch (FileNotFoundException fnfe) {

                }
                br = new BufferedReader(fr);
                try {
                    while ((fileLine = br.readLine()) != null) {
                        String[] line = fileLine.split(",");
                        
                        //ID is the instanceName from Cpp2Java.h
                        int ID = Integer.parseInt(line[0]);
                        
                        switch (line[1]) {      //Type of Command
                            case "removeAll":
                                {
                                   frame.contents.removeAll();
                                    frame.getContentPane().removeAll();
                                }
                                break;
                            case "instantiate":   
                                {
                                    switch (line[3]) {   // Type of JComponent
                                        case "JPanel":
                                            comps.add(ID, new JPanel());
                                            break;
                                        case "JLabel":
                                          {
                                             switch(Integer.parseInt(line[2]))   {     // Type of Constructor Method
                                                case 0:
                                                   comps.add(ID, new JLabel(line[4]));
                                                break;
                                                case 1:
                                                   comps.add(ID, new JLabel(line[4], Integer.parseInt(line[5])));
                                                break;
                                             }
                                          }
                                            break;
                                        case "JTextField":
                                          {
                                             switch(Integer.parseInt(line[2]))   {
                                                case 0:
                                                   comps.add(ID, new JTextField(line[4], Integer.parseInt(line[5])));
                                                break;
                                                case 1:
                                                   comps.add(ID, new JTextField(Integer.parseInt(line[4])));
                                                break;
                                             }
                                          }
                                            break;
                                        case "JTextArea":
                                           {
                                             switch(Integer.parseInt(line[2]))   {
                                                case 0:
                                                   comps.add(ID, new JTextArea(line[4]));
                                                break;
                                                case 1:
                                                   comps.add(ID, new JTextArea(Integer.parseInt(line[4]),Integer.parseInt(line[5])));
                                                break;
                                                case 2:
                                                   comps.add(ID, new JTextArea(Integer.parseInt(line[4]),Integer.parseInt(line[5],Integer.parseInt(line[6]) )));
                                                break;
                                             }
                                           }
                                            break;
                                        case "JButton":
                                          {
                                             switch(Integer.parseInt(line[2]))   {
                                                case 0:
                                                   comps.add(ID, new JButton());
                                                break;
                                                case 1:
                                                   comps.add(ID, new JButton(line[4]));
                                                break;
                                             }
                                          }
                                            break;
                                        default:
                                            break;
                                            //JTextField
                                            //JButton
                                    }
                                }
                                break;
                            case "setText":
                                {
                                    ((JLabel) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
                                }
                                break;
                            case "add":
                                {
                                    // Command [1] is the JComponent you're adding TO
                                    // Command [2] is the JComponent that you're adding
                                    comps.get(Integer.parseInt(line[0])).add(comps.get(Integer.parseInt(line[2])));
                                }
                                break;
                            default:
                                break;
                        }
                    }
                } catch (IOException ioe) {}
                for (JComponent jc: comps) {
                    if (jc instanceof JPanel)
                     frame.contents.add(jc);
                }
                frame.revalidate();
                frame.repaint();
            }
        };

        java.util.Timer timer = new java.util.Timer();
        // repeat the check every second
        timer.schedule(task, new Date(), 1);
    }
}