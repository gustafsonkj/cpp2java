// Test_Interface.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include "Cpp2Java.h"
int main()
{
	Cpp2Java Cpp2Java;

	Cpp2Java.removeAll();
	Cpp2Java.setLayout(new BorderLayout());

	JPanel myPanel;
	JPanel panel2;
	JLabel myLabel("Hola!");
	JLabel label2("Whats up?");
	myPanel.add(myLabel);
	panel2.add(label2);
	Cpp2Java.add(myPanel, "BorderLayout.SOUTH");
	Cpp2Java.add(panel2, "BorderLayout.SOUTH");
	
	Cpp2Java.finish();

	this_thread::sleep_for(chrono::milliseconds(1000));

	for (int i = 0; i < 100; i++)
	{
		myPanel.clearRect(0, 0, 600, 600);
		myPanel.drawRect(i,i,2*i,2*i);
		myPanel.repaint();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	for (int i = 100; i > -1; i--)
	{
		myPanel.clearRect(0, 0, 600, 600);
		//myPanel.drawString
		myPanel.drawRect(i, i, 2 * i, 2 * i);
		myPanel.repaint();
		this_thread::sleep_for(chrono::milliseconds(50));
	}
	return 0;
}

