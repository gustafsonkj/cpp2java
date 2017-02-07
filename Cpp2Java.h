#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

static class Cpp2Java
{
public:

	ofstream file;
	string removeAll;


	//methods go here


	void removeAll()
	{
		file.open("temp.txt");
		file.clear();
		
		removeAll = "removeAll \n";

		file << removeAll;

		file.close();
	};



};

