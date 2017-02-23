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

                // here we code the action on a change
                System.out.println("File " + file.getName() + " have change !");
                try {
                    fr = new FileReader(new File("text.csv"));
                } catch (FileNotFoundException fnfe) {

                }
                br = new BufferedReader(fr);
                ArrayList < JComponent > comps = new ArrayList < JComponent > (64);
                try {
                    while ((fileLine = br.readLine()) != null) {
                        String[] line = fileLine.split(",");
                        switch (line[0]) {
                            case "removeAll":
                                {
                                    contents.removeAll();
                                    frame.getContentPane().removeAll();

                                }
                                break;
                            case "instantiate":
                                {
                                    switch (line[1]) {
                                        case "JPanel":
                                            comps.add(Integer.parseInt(line[2]), new JPanel());
                                            System.out.println("Addedpanel");
                                            break;
                                        case "JLabel":
                                            comps.add(Integer.parseInt(line[3]), new JLabel(line[2]));
                                            System.out.println("Addedlbael");
                                            break;
                                        case "JTextArea": //comps[line[2]] = new JTextArea();
                                            break;
                                        case "JTextField": //comps[line[2]] = new JTextField();
                                            break;
                                        case "JButton": //comps[line[2]] = new JButton();
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
                                    comps.get(Integer.parseInt(line[1])).add(comps.get(Integer.parseInt(line[2])));
                                }
                                break;
                        }
                    }
                } catch (IOException ioe) {}
                for (JComponent jc: comps) {
                    contents.add(jc);
                }
                frame.revalidate();
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
        timer.schedule(task, new Date(), 1);
    }
}