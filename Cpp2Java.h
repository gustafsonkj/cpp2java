#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

class Commands
{
public:
	vector<string> commands;
	vector<string> paint;
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
	virtual void drawRect(int x, int y, int width, int height);
	virtual void repaint();
	ofstream file;
protected:
	void setInstanceName();
	string instanceName;

};
void JComponent::add(JComponent & jc)
{
	c.commands.push_back("add," + instanceName + "," + jc.instanceName);
}
void JComponent::drawRect(int x, int y, int width, int height)
{
	c.paint.push_back("drawRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height) + "," + instanceName);
}
void JComponent::repaint()
{
	ofstream file1;
	file1.open("test1.csv");
	for (string s : c.paint)
	{
		file1 << s + "\n";
	}
	file1.close();
	c.paint.clear();
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
	file << "end" << endl;
	file.close();
}
void Cpp2Java::setLayout(string  s)
{
	c.commands.push_back("setLayout," + s);
}

