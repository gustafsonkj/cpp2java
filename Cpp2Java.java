import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

public class Cpp2Java extends JFrame { //One-JFrame setup
    private static Container contents;
    private ArrayList < JComponent > comps = new ArrayList < JComponent > (64);
    private ArrayList < ButtonGroup> butts = new ArrayList < ButtonGroup > (64);

    private class GuiThread extends Thread {
        public void run() {
            while (true) {
                ArrayList < String > cmnds = new ArrayList < String > (64);

                boolean busyWait1 = true;
                RandomAccessFile pipe = null;
                while (busyWait1) {
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ie) {}
                    try {
                        pipe = new RandomAccessFile("\\\\.\\pipe\\Cpp2Java_gui", "r");
                        busyWait1 = false;
                    } catch (FileNotFoundException e1) {
                        // e1.printStackTrace();
                    }
                }
                // Main loop
                try {
                    String inData = "";
                    while ((inData = pipe.readLine()) != null) {

                        // Read from the pipe one line at a time
                        //inData = pipe.readLine();
                        if (inData != null) {
                            cmnds.add(inData);
                            ////System.out.println("Read from pipe :" + inData); //**Here it prints with spaces**

                            //parseData(inData);
                        }

                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
                // Close the pipe at the end
                // //System.out.println("here0");

                try {
                    pipe.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                ////System.out.println("here");
                performCommands(cmnds);
                revalidate();
                repaint();
            }
        }
    }
    private class PaintThread extends Thread {
        public void run() {
            while (true) {
                boolean busyWait1 = true;
                RandomAccessFile pipe = null;
                while (busyWait1) {
                    try {
                        Thread.sleep(10);
                    } catch (InterruptedException ie) {}
                    try {
                        pipe = new RandomAccessFile("\\\\.\\pipe\\Cpp2Java_paint", "r");
                        busyWait1 = false;
                    } catch (FileNotFoundException e1) {
                        // e1.printStackTrace();
                    }
                }
                //while(true)   {
                   try {
                        Thread.sleep(10);
                    } catch (InterruptedException ie) {}
                   // Main loop
                   try {
                       String fileLine = "";
                       while ((fileLine = pipe.readLine()) != null) {
                           String[] line = fileLine.split(",");
                           String command = "";
                           for (int i = 1; i < line.length; i++) {
                               command += line[i] + ",";
                           }
                           System.out.println(command);
                           /* Object comp = comp.get...
                           if (comp instanceof DynamicJanel)
                              (Dynamic)...*/
                           ((DynamicJPanel) comps.get(Integer.parseInt(line[0]))).setCommand(command);
   
                           //ID is the instanceName from Cpp2Java.h
                           int ID = Integer.parseInt(line[0]);
                           try {
                               Thread.sleep(5);
                           } catch (InterruptedException ie) {}
   
                           ((DynamicJPanel) comps.get(Integer.parseInt(line[0]))).repaint();
                       }
   
                   } catch (IOException ioe) {}
                //}
                // Close the pipe at the end
                // //System.out.println("here0");

                try {
                    pipe.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }

            }
        }
    }

    //private ArrayList<JComponent>();
    public Cpp2Java() {
        super("Cpp2Java");
        contents = getContentPane();
        contents.setLayout(new GridLayout(2, 2));

        setSize(720, 540);
        setVisible(true);

        GuiThread gui = new GuiThread();
        PaintThread pnt = new PaintThread();

        gui.start();
        pnt.start();
        startPipe();
    }

    public static void main(String args[]) {
            // monitor a single file
            Cpp2Java frame = new Cpp2Java();

            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);


        } //Main   
    
    public static RandomAccessFile pipe;
    public static void startPipe()
    {
      boolean busyWait1 = true;
                pipe = null;
                while (busyWait1) {
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException ie) {}
                    try {
                        pipe = new RandomAccessFile("\\\\.\\pipe\\Java2Cpp", "rw");
                        busyWait1 = false;
                    } catch (FileNotFoundException e1) {
                        // e1.printStackTrace();
                    }
                }
    }
    public static void sendCommandThroughPipe(String command)  {
               
                               // Main loop
                try {
                    pipe.writeBytes(command);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                // Close the pipe at the end
                // //System.out.println("here0");

                /*try {
                    pipe.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }*/
               

    }
    
    public void performCommands(ArrayList < String > cmnds) {
        //this.contents.removeAll();
        //this.getContentPane().removeAll();
        for (String l: cmnds) {
            ////System.out.println(l);

            String[] line = l.split(",");
            int ID = Integer.parseInt(line[0]);
            int nRows;
            int nCols;
            int hGap;
            int vGap;
         
            switch (line[1]) { //Type of Command
                case "addActionListener":
                    {
                        
                        //System.out.println(comps.get(ID).getClass().getName());
                        comps.get(ID).setFocusable(false); //Wasnt working so needed this
                       
                       if ( comps.get(ID) instanceof JButton) //If component is a DynamicJButton
                        {
                           System.out.println("Its a button!");
                             ((DynamicJButton)comps.get(ID)).addActionListener();
                            
                        } else if (comps.get(ID) instanceof JTextField) //If component is a DynamicTextField
                        {
                            ((DynamicJTextField) comps.get(ID)).addActionListener();
                        }
                    }
                    break;
                case "removeAll":
                    {
                        comps.clear();
                        this.contents.removeAll();
                        this.getContentPane().removeAll();
                    }
                    break;
                case "instantiate":
                    {
                        switch (line[3]) { // Type of JComponent
                            case "JPanel":
                                comps.add(ID, new DynamicJPanel());
                                break;
                            case "JComboBox":
                                comps.add(ID, new JComboBox());
                                break;
                            case "JLabel":
                                {
                                    switch (Integer.parseInt(line[2])) { // Type of Constructor Method
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
                                    switch (Integer.parseInt(line[2])) {
                                        case 0:
                                            comps.add(ID, new DynamicJTextField(line[4], Integer.parseInt(line[5]), ID));
                                            break;
                                        case 1:
                                            comps.add(ID, new DynamicJTextField(Integer.parseInt(line[4]), ID));
                                            break;
                                    }
                                }
                                break;
                            case "JTextArea":
                                {
                                    switch (Integer.parseInt(line[2])) {
                                        case 0:
                                            comps.add(ID, new JTextArea(line[4]));
                                            break;
                                        case 1:
                                            comps.add(ID, new JTextArea(Integer.parseInt(line[4]), Integer.parseInt(line[5])));
                                            break;
                                        case 2:
                                            comps.add(ID, new JTextArea(
                                                Integer.parseInt(line[4]), Integer.parseInt(line[5], Integer.parseInt(line[6]))));
                                            break;
                                    }
                                }
                                break;
                            case "JButton":
                                {
                                    switch (Integer.parseInt(line[2])) {
                                        case 0:
                                            comps.add(ID, new DynamicJButton(ID));
                                            break;
                                        case 1:
                                            //System.out.println("ch3");
                                            comps.add(ID, new DynamicJButton(ID, line[4]));
                                            break;
                                    }
                                }
                                break;
                            case "ButtonGroup":
                              butts.add(ID, new ButtonGroup());
                            break;
                            
                            case "JRadioButton":
                              comps.add(ID, new JRadioButton(line[4]));
                            break;
                            
                            case "JCheckBox":
                              comps.add(ID, new JCheckBox(line[4]));
                            break;
                            
                            default:
                                break;
                                //JTextField
                                //JButton
                        }
                    }
                    break;
                case "addItemToComboBox":
                  {
                     System.out.println(line[2]);
                      ( (JComboBox)comps.get(ID) ).addItem( (line[2]) );
                  }
                  break;
                 case "addToButtonGroup":
                  {
                  
                     System.out.println(line[2]);
                     
                    if ( comps.get(Integer.parseInt(line[2])) instanceof JRadioButton)
                    {
                      ( (ButtonGroup)butts.get(ID) ).add
                        ( 
                           (JRadioButton) ( comps.get(Integer.parseInt(line[2])) )
                        );
                    }
                    else if ( comps.get(Integer.parseInt(line[2])) instanceof JCheckBox)
                    {
                      ( (ButtonGroup)butts.get(ID) ).add
                        ( 
                           (JCheckBox) ( comps.get(Integer.parseInt(line[2])) )
                        );
                    }
                  }
                  break;
                case "setTextJL":
                    {
                        System.out.println(line[2]);
                        ((JLabel) comps.get(Integer.parseInt(line[0]))).setText(line[2]);
                    }
                    break;

                case "setTextJTA":
                    {
                        ((JTextArea) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
                    }
                    break;

                case "setTextJTF":
                    {
                        ((JTextField) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
                    }

                case "setLayout":
                    {
                        switch (line[2]) {
                            case "GridLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            comps.get(ID).setLayout(new GridLayout(nRows, nCols));
                                            break;
                                        case 1:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            hGap = Integer.parseInt(line[6]);
                                            vGap = Integer.parseInt(line[7]);
                                            comps.get(ID).setLayout(new GridLayout(nRows, nCols, hGap, vGap));
                                            break;
                                    }
                                }
                                break;
                            case "BorderLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            comps.get(ID).setLayout(new BorderLayout());
                                            break;
                                        case 1:
                                            hGap = Integer.parseInt(line[4]);
                                            vGap = Integer.parseInt(line[5]);
                                            comps.get(ID).setLayout(new BorderLayout(hGap, vGap));
                                            break;
                                    }

                                }
                                break;
                        }
                    }
                    break;

                    // JComponent Methods
                case "add":
                    {
                        // Command [1] is the JComponent you're adding TO
                        // Command [2] is the JComponent that you're adding
                        String layout;
                        String layoutID;
                        try {
                            layout = line[3];
                            switch (layout) {
                                case "BorderLayout.NORTH":
                                    layoutID = BorderLayout.NORTH;
                                    break;
                                case "BorderLayout.EAST":
                                    layoutID = BorderLayout.EAST;
                                    break;
                                case "BorderLayout.SOUTH":
                                    layoutID = BorderLayout.SOUTH;
                                    break;
                                case "BorderLayout.WEST":
                                    layoutID = BorderLayout.WEST;
                                    break;
                                case "BorderLayout.CENTER":
                                    layoutID = BorderLayout.CENTER;
                                    break;
                                default:
                                    layoutID = BorderLayout.CENTER;
                                    break;
                            }
                            comps.get(ID).add(comps.get(Integer.parseInt(line[2])), layoutID);
                        } catch (IndexOutOfBoundsException ie) {
                            comps.get(ID).add(comps.get(Integer.parseInt(line[2])));
                        }
                    }

                    // comps_add.add(
                    break;

                case "setForeground":
                    comps.get(ID).setForeground(Color.decode(line[2]));
                    break;

                case "setBackground":
                    comps.get(ID).setBackground(Color.decode(line[2]));
                    break;


                    // Container Methods
                case "setContainerLayout":
                    {
                        switch (line[2]) {
                            case "GridLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            this.contents.setLayout(new GridLayout(nRows, nCols));
                                            break;
                                        case 1:
                                            nRows = Integer.parseInt(line[4]);
                                            nCols = Integer.parseInt(line[5]);
                                            hGap = Integer.parseInt(line[6]);
                                            vGap = Integer.parseInt(line[7]);
                                            this.contents.setLayout(new GridLayout(nRows, nCols, hGap, vGap));
                                            break;
                                    }
                                }
                                break;
                            case "BorderLayout":
                                {
                                    switch (Integer.parseInt(line[3])) {
                                        case 0:
                                            this.contents.setLayout(new BorderLayout());
                                            break;
                                        case 1:
                                            hGap = Integer.parseInt(line[4]);
                                            vGap = Integer.parseInt(line[5]);
                                            this.contents.setLayout(new BorderLayout(hGap, vGap));
                                            break;
                                    }

                                }
                                break;
                        }
                    }
                    break;
                case "addContainer":
                    {
                        String layout;
                        String layoutID;
                        try {
                            layout = line[4];
                            switch (layout) {
                                case "BorderLayout.NORTH":
                                    layoutID = BorderLayout.NORTH;
                                    break;
                                case "BorderLayout.EAST":
                                    layoutID = BorderLayout.EAST;
                                    break;
                                case "BorderLayout.SOUTH":
                                    layoutID = BorderLayout.SOUTH;
                                    break;
                                case "BorderLayout.WEST":
                                    layoutID = BorderLayout.WEST;
                                    break;
                                case "BorderLayout.CENTER":
                                    layoutID = BorderLayout.CENTER;
                                    break;
                                default:
                                    layoutID = BorderLayout.CENTER;
                                    break;
                            }
                            this.contents.add(comps.get(Integer.parseInt(line[2])), layoutID);
                        } catch (IndexOutOfBoundsException ie) {
                            this.contents.add(comps.get(Integer.parseInt(line[2])));
                        }
                    }
                    break;
                case "addKeyListener":
                    //System.out.println("CH4");
                    contents.addKeyListener(new DynamicKeyAdapter());
                    contents.setFocusable(true);
                    contents.requestFocusInWindow();

                    break;
                case "addMouseListener":
                    contents.addMouseListener(new DynamicMouseListener());
                    break;
            }
            System.out.println(comps.size());

        }
    }
}