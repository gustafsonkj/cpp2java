import java.util.Vector;
import javax.swing. * ;
import java.awt. * ;

public class DynamicJPanel extends JPanel {
	private Vector < String > commands = new Vector<String>();

	public void setCommand(String command) {
		commands.add(command);
	}
	public void paintComponent(Graphics g) {
		super.paintComponent(g);

		try {
			for (String C: commands) {
				String[] command = C.split(",");
				switch (command[0]) {
				case "drawRect":
					g.drawRect(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "drawLine":
					g.drawLine(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "fillRect":
					g.fillRect(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "clearRect":
					g.clearRect(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "drawOval":
					g.drawOval(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "fillOval":
					g.fillOval(Integer.parseInt(command[1]), Integer.parseInt(command[2]), Integer.parseInt(command[3]), Integer.parseInt(command[4]));
					break;

				case "drawString":
					g.drawString(command[1], Integer.parseInt(command[2]), Integer.parseInt(command[3]));
					break;

				}
			}
		}
		catch(NullPointerException npe) {}

	}
}