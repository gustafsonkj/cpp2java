// Test_Interface.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "Cpp2Java.h"
int main()
{
	Cpp2Java Cpp2Java;

	Cpp2Java.removeAll();

	JPanel myPanel;
	JPanel myPanel2;
	JPanel myPanel3;
	JLabel myLabel("Hff");
	JLabel myLabel2("fs");
	JButton myButton0("MUTTON!");
	JButton myButton1("MY BUTON!");
	JButton myButton2("MY11!");
	JLabel myLabel3("three");
	JLabel myLabel4("fpour");

	myPanel.add(myLabel);
	myPanel.add(myLabel2);
	myPanel2.add(myButton0);
	myPanel2.add(myButton1);
	myPanel2.add(myButton2);
	myPanel3.add(myLabel3);
	myPanel3.add(myLabel4);

	Cpp2Java.add(myPanel);
	Cpp2Java.add(myPanel2);
	Cpp2Java.add(myPanel3);
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
		myPanel.drawRect(i, i, 2 * i, 2 * i);
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
	return 0;
}

