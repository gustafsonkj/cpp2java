#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

static class Cpp2Java
{
public:

	ofstream file;
	string javaCode;










	void clearAll()
	{
		file.open("code.Java");
		file.clear();
		
		file << javaCode;

		file.close();
	};


Cpp2Java.drawLine();
Cpp2Java.removeAll();
};

