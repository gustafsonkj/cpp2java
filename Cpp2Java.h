#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Commands
{
public:
	vector<string> commands;
	int instanceCounter;
};
Commands c;

class Polygon
{
public:
	void addPoint(int x, int y);
};
void Polygon::addPoint(int x, int y)
{

}

class JComponent
{
	friend class Cpp2Java;
public:
	virtual void add(JComponent & jc);
	ofstream file;
protected:
	void setInstanceName();
	string instanceName;

};
void JComponent::add(JComponent & jc)
{
	c.commands.push_back("add," + instanceName + "," + jc.instanceName);
}
void JComponent::setInstanceName()
{
	instanceName = to_string(c.instanceCounter);
	c.instanceCounter++;
}

class JPanel : public JComponent
{
public:
	JPanel();
};
JPanel::JPanel()
{
	setInstanceName();
	c.commands.push_back("instantiate,JPanel," + instanceName);
}

class JLabel : public JComponent
{
public:
	JLabel(string s);
	void setText(string s);
};
JLabel::JLabel(string s)
{
	setInstanceName();
	c.commands.push_back("instantiate,JLabel," + s + "," + instanceName);
}
void JLabel::setText(string s)
{
	c.commands.push_back("setText," + s + "," + instanceName);
}

class Cpp2Java
{
public:
	Cpp2Java();
	void removeAll();
	void finish();
	void setLayout(string s);
	ofstream file;
private:
	JComponent * JC;
};
Cpp2Java::Cpp2Java()
{
	JC = new JComponent();
}
void Cpp2Java::removeAll()
{
	string removeAll;
	file.open("text.csv");
	file.clear();

	removeAll = "removeAll \n";

	file << removeAll;

}
void Cpp2Java::finish()
{
	for (string s : c.commands)
	{
		file << s + "\n";
	}

	file.close();
}
void Cpp2Java::setLayout(string s)
{
	c.commands.push_back("setLayout," + s);
}

