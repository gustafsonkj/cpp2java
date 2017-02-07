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
		file.open("temp.txt");
		file.clear();
		
		file << javaCode;

		file.close();
	};



};

