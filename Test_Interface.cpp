// Test_Interface.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
			for (int i = 0; i < 100; i++)
			{
				myPanel1.clearRect(0, 0, 600, 600);
				myPanel1.drawRect(20, 20, i, i);
				myPanel1.drawString(to_string(i), i, i);
				myPanel1.repaint();
				this_thread::sleep_for(chrono::milliseconds(30));
			}
		}
	};

	KeyHandler myKH;
	Cpp2Java.addKeyListener(myKH);
	Cpp2Java.finish();

	//WAIT TWO SECONDS
	this_thread::sleep_for(chrono::milliseconds(50));
	/*
	//DRAW RECTANGLE
	for (int i = 0; i < 100; i++)
	{
		myPanel1.clearRect(0, 0, 600, 600);
		myPanel1.drawRect(20, 20, i, i);
		myPanel1.drawString(to_string(i), i, i);
		myPanel1.repaint();
		this_thread::sleep_for(chrono::milliseconds(30));
	}

	this_thread::sleep_for(chrono::milliseconds(2000));

	//CIRCLE DOWN
	for (int i = 100; i > -1; i--)
	{
		myPanel1.clearRect(0, 0, 600, 600);
		myPanel1.drawOval(i, i, 2 * i, 2 * i);
		myPanel1.drawString(to_string(i), i, i);
		myPanel1.repaint();
		this_thread::sleep_for(chrono::milliseconds(30));
	}
	*/
	while (1);
	
}

