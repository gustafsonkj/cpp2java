#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

static class Cpp2Java
{
public:

	//methods declared here
	void removeAll();


};

// methods written down here

void Cpp2Java::removeAll()
{
	ofstream file;
	string removeAll;
	file.open("text.txt");
	file.clear();

	removeAll = "removeAll \n";

	file << removeAll;

	file.close();
}

