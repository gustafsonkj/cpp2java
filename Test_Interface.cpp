// Test_Interface.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "Cpp2Java.h"



JPanel myPanel;
JPanel myPanel2;
JPanel myPanel3;
JLabel myLabel("Label 1");
JLabel myLabel2("Label 2");
JButton myButton0("First Button!");
JButton myButton1("Second Button!");
JButton myButton2("Third Button!");
JLabel myLabel3("Label 3");
JLabel myLabel4_1("GridPanel_4_1");
JLabel myLabel4_2("GridPanel_4_2");
JLabel myLabel4_3("GridPanel_4_3");
JLabel myLabel4_4("GridPanel_4_4");
Image myTestImage("testImage.gif");

int main() {
	Cpp2Java Cpp2Java;

	Cpp2Java.removeAll();

	// SET J FRAME LAYOUT
	Cpp2Java.setLayout(new GridLayout(2, 2));
	
	if (myPanel == myPanel2)
		cout << "1 and 2 equal" << endl;
	if (myPanel == myPanel)
		cout << "equal to self" << endl;


	for (int i = 0; i < jComps.size(); i++)
		cout << jComps[i] << endl;
	// INSTANTIATE "COMPONENTS"
	class ActionHandler : public ActionListener
	{
	public:
		void actionPerformed(ActionEvent * ae)
		{
			cout << "Test" << endl;
			cout << "FIRST:" << ae->getSource().getInstanceName() << endl;
			cout << "SECOND:" << myButton1.getInstanceName() << endl;
			if (ae->getSource() == myButton1)
				cout << "stuff";
		};

	};
	cout << "test1" << endl;

	ActionHandler* myAH = new ActionHandler();
	cout << "test2"<<endl;

	myButton1.addActionListener(myAH);
	cout << "test3" << endl;

	myAH->actionPerformed(new ActionEvent(stoi(myButton1.getInstanceName())));
	myPanel.add(myLabel);
	myPanel2.add(myButton2);

	//if (ae.getSource()==myButton1)

	// SET SPECIAL PANEL LAYOUT
	myPanel3.setLayout(new GridLayout(2, 2));

	myPanel3.add(myLabel4_1);
	myPanel3.add(myLabel4_2);
	myPanel3.add(myLabel4_3);
	myPanel3.add(myLabel4_4);

	// ADD THINGS
	Cpp2Java.add(myPanel);
	Cpp2Java.add(myPanel2);
	myPanel.add(myLabel2);
	myPanel2.add(myButton0);
	myPanel2.add(myButton1);
	Cpp2Java.add(myPanel3);


	Cpp2Java.finish();

	//WAIT TWO SECONDS
	this_thread::sleep_for(chrono::milliseconds(2000));

	//DRAW RECTANGLE
	for (int i = 0; i < 100; i++)
	{
		myPanel.clearRect(0, 0, 600, 600);
		myPanel.drawRect(20, 20, i, i);
		myPanel.drawString(to_string(i), i, i);
		myPanel.repaint();
		this_thread::sleep_for(chrono::milliseconds(20));
	}
	myPanel2.drawImage(myTestImage, 0, 0);

	this_thread::sleep_for(chrono::milliseconds(2000));

	//CIRCLE DOWN
	for (int i = 100; i > -1; i--)
	{
		myPanel.clearRect(0, 0, 600, 600);
		myPanel.drawOval(i, i, 2 * i, 2 * i);
		myPanel.drawString(to_string(i), i, i);
		myPanel.repaint();
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	/*
	string test = "a";
	for (int i = 0; i < 20; i++)
	{
		test += "a";
		Cpp2Java.removeAll();
		myLabel.setText(test);
		Cpp2Java.finish();
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	test = "c";
	for (int i = 0; i < 20; i++)
	{
		test += "c";
		Cpp2Java.removeAll();
		myLabel.setText(test);
		Cpp2Java.finish();
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	*/


}