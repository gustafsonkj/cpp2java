#include "Cpp2Java.h"


JPanel myPanel1;
JPanel myPanel2;
JPanel myPanel3;
JPanel myPanel4;
JButton myBtn1("H,1");
//JButton myBtn11("H,1fasf");
JButton myBtn2("H,elasdflo2");
JButton myBtn3("H,ellasfdo3");
JButton myBtn4("H,ellasdflo4");

int main() {
	Cpp2Java Cpp2Java;

	//Cpp2Java.removeAll();

	// SET J FRAME LAYOUT
	Cpp2Java.setLayout(new GridLayout(2, 2));



	/*for (int i = 0; i < jComps.size(); i++)
	cout << jComps[i] << endl;*/
	// INSTANTIATE "COMPONENTS"


	//myAH->actionPerformed(new ActionEvent(stoi(myButton1.getInstanceName())));

	myPanel1.add(myBtn1);
	myPanel2.add(myBtn2);
	//myPanel2.add(myBtn11);
	myPanel3.add(myBtn3);
	myPanel4.add(myBtn4);
	Cpp2Java.add(myPanel1);
	Cpp2Java.add(myPanel2);
	Cpp2Java.add(myPanel3);
	Cpp2Java.add(myPanel4);

	class KeyHandler : public KeyListener
	{
	public:
		void keyReleased(KeyEvent ke)
		{
			//cout << "key Released!" << endl;
			//cout << ke.getKeyChar() << endl;
			myPanel1.clearRect(0, 0, 600, 600);
			myPanel1.drawString(ke.getKeyChar(), 20, 20);
			myPanel1.repaint();
			//DRAW RECTANGLE
			/*for (int i = 0; i < 100; i++)
			{
			myPanel1.clearRect(0, 0, 600, 600);
			myPanel1.drawRect(20, 20, i, i);
			myPanel1.drawString(to_string(i), i, i);
			myPanel1.repaint();
			this_thread::sleep_for(chrono::milliseconds(30));
			}*/
		}
	};

	KeyHandler myKH;
	Cpp2Java.addKeyListener(myKH);
	//Cpp2Java.finish();
	this_thread::sleep_for(chrono::milliseconds(50));


	class ActionHandler : public ActionListener
	{
	public:
		void actionPerformed(ActionEvent ae)
		{
			cout << "Test" << endl;
			cout << "FIRST:" << ae.getSource().getInstanceName() << endl;
			cout << "SECOND:" << myBtn1.getInstanceName() << endl;
			if (ae.getSource() == myBtn1)
				cout << "stuff";
		};

	};
	//cout << "test1" << endl;

	////ActionHandler* myAH = new ActionHandler;
	ActionHandler myAH;
	//cout << "test2" << endl;

	myBtn1.addActionListener(myAH);
	Cpp2Java.finish();
	this_thread::sleep_for(chrono::milliseconds(50));

	cout << "test3" << endl;

	while (1);

}