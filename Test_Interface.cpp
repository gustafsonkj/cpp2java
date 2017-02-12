// Test_Interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Cpp2Java.h"

int main()
{
	Cpp2Java Cpp2Java;
	Cpp2Java.removeAll();

	JPanel myPanel;
	JLabel myLabel("Hello World");

	myPanel.add(myLabel);

	for (int i = 0; i < 50; i++)
	{
		myPanel.drawRect(0, 0, i, 50);
		this_thread::sleep_for(.02s);
	}
	myPanel.repaint();

	Cpp2Java.finish();
    return 0;
}

