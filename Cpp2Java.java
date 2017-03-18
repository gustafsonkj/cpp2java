import java.awt. * ;
import javax.swing. * ;
import java.awt.event. * ;
import java.io. * ;
import java.util. * ;

public class Cpp2Java extends JFrame { //One-JFrame setup
	private static Container contents;
	//private ArrayList<JComponent>();
	public Cpp2Java() {
		super("Cpp2Java");
		contents = getContentPane();
		contents.setLayout(new GridLayout(2, 2));
		setSize(720, 540);
		setVisible(true);

	}
	public static void main(String args[]) {
		// monitor a single file
		Cpp2Java frame = new Cpp2Java();

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		ArrayList < JComponent > comps = new ArrayList < JComponent > (64);
		//frame.revalidate();

		TimerTask gui = new FileWatcher(new File("Cpp2Java_gui.csv")) {
			FileReader fr;
			BufferedReader br;
			String fileLine;
			protected void onChange(File file) {

				// here we code the action on a change
				//System.out.println("File " + file.getName() + " have change !");
				try {
					fr = new FileReader(new File("Cpp2Java_gui.csv"));
				} catch(FileNotFoundException fnfe) {

}
				br = new BufferedReader(fr);
				try {
					while ((fileLine = br.readLine()) != null) {
						String[] line = fileLine.split(",");

						//ID is the instanceName from Cpp2Java.h
						int ID = Integer.parseInt(line[0]);
						int nRows;
						int nCols;
						int hGap;
						int vGap;

						switch (line[1]) { //Type of Command
                  case "addActionListener":
                  {
                     //need to add actionlistener to the type and instance of jcomponent passed in
                     //will use dynamic action listener class that zac created to do this
                     //DynamicActionListener.addActionListener(comps[ID]);
                  }
						case "removeAll":
							{
								comps.clear();
								frame.contents.removeAll();
								frame.getContentPane().removeAll();
							}
							break;
						case "instantiate":
							{
								switch (line[3]) { // Type of JComponent
								case "JPanel":
									comps.add(ID, new DynamicJPanel());
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
						case "setTextJL":
							{ ((JLabel) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
							}
							break;

						case "setTextJTA":
							{ ((JTextArea) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
							}
							break;

						case "setTextJTF":
							{ ((JTextField) comps.get(Integer.parseInt(line[2]))).setText(line[1]);
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
                        try
                           {
                              layout = line[3];
                              switch (layout)   {
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
                           }
                        catch (IndexOutOfBoundsException ie)
                           {
                              comps.get(ID).add(comps.get(Integer.parseInt(line[2])));
                           }
							}

							// comps_add.add(
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
											frame.contents.setLayout(new GridLayout(nRows, nCols));
											break;
										case 1:
											nRows = Integer.parseInt(line[4]);
											nCols = Integer.parseInt(line[5]);
											hGap = Integer.parseInt(line[6]);
											vGap = Integer.parseInt(line[7]);
											frame.contents.setLayout(new GridLayout(nRows, nCols, hGap, vGap));
											break;
										}
									}
									break;
								case "BorderLayout":
									{
										switch (Integer.parseInt(line[3])) {
										case 0:
											frame.contents.setLayout(new BorderLayout());
											break;
										case 1:
											hGap = Integer.parseInt(line[4]);
											vGap = Integer.parseInt(line[5]);
											frame.contents.setLayout(new BorderLayout(hGap, vGap));
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
                        try
                           {
                              layout = line[4];
                              switch (layout)   {
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
                              frame.contents.add(comps.get(Integer.parseInt(line[2])), layoutID);
                           }
                        catch (IndexOutOfBoundsException ie)
                           {
                              frame.contents.add(comps.get(Integer.parseInt(line[2])));
                           }
							}
							}
						//default:
							//break;
						}
					}
				catch(IOException ioe) {}
				frame.revalidate();
				frame.repaint();
			}
		};

		TimerTask painter = new FileWatcher(new File("Cpp2Java_paint.csv")) {
			FileReader fr;
			BufferedReader br;
			String fileLine;
			protected void onChange(File file) {

				//System.out.println("Paint file: " + file.getName() + " have change !");
				try {
					fr = new FileReader(new File("Cpp2Java_paint.csv"));
				} catch(FileNotFoundException fnfe) {

}
				br = new BufferedReader(fr);
				try {
					while ((fileLine = br.readLine()) != null) {
						String[] line = fileLine.split(",");
						String command = "";
						for (int i = 1; i < line.length; i++) {
							command += line[i] + ",";
						}

						/* Object comp = comp.get...
                        if (comp instanceof DynamicJanel)
                           (Dynamic)...*/
						((DynamicJPanel) comps.get(Integer.parseInt(line[0]))).setCommand(command);

						//ID is the instanceName from Cpp2Java.h
						int ID = Integer.parseInt(line[0]);
						((DynamicJPanel) comps.get(Integer.parseInt(line[0]))).repaint();
					}

				} catch(IOException ioe) {}

			}
		};
		java.util.Timer timer = new java.util.Timer();
		// repeat the check every second
		timer.schedule(gui, new Date(), 100);
		timer.schedule(painter, new Date(), 10);
	} //Painter
}