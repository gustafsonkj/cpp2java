#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

class Java
{
public:

	ifstream file;
	string address;
	string javaCode;

	void clearAll()
	{
		cin >> address;
		file.open(address);
		file.clear();
		
		

		file.close();
	};

	void drawLine()
	{

	};

};

