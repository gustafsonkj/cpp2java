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
	virtual void drawRect(int x, int y, int width, int height, bool isPermanent);
	virtual void drawLine(int xStart, int yStart, int xEnd, int yEnd, bool isPermanent);
	virtual void fillRect(int x, int y, int width, int height, bool isPermanent);
	virtual void clearRect(int x, int y, int width, int height, bool isPermanent);
	virtual void drawOval(int x, int y, int width, int height, bool isPermanent);
	virtual void fillOval(int x, int y, int width, int height, bool isPermanent);
	virtual void drawPolygon(Polygon p);
	virtual void fillPolgon(Polygon p);
	virtual void drawString(string s, int x, int y, bool isPermanent);
	virtual void repaint();
	ofstream file1;
protected:
	void setInstanceName();
	string instanceName;

};
void JComponent::add(JComponent & jc)
{
	c.commands.push_back("add," + instanceName + "," + jc.instanceName);
}
void JComponent::drawRect(int x, int y, int width, int height, bool isPermanent)
{
	c.paint.push_back("drawRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::drawLine(int xStart, int yStart, int xEnd, int yEnd, bool isPermanent)
{
	c.paint.push_back("drawLine," + to_string(xStart) + "," + to_string(yStart) + "," + to_string(xEnd) + "," + to_string(yEnd) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::fillRect(int x, int y, int width, int height, bool isPermanent)
{
	c.paint.push_back("fillRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::clearRect(int x, int y, int width, int height, bool isPermanent)
{
	c.paint.push_back("clearRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::drawOval(int x, int y, int width, int height, bool isPermanent)
{
	c.paint.push_back("drawOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::fillOval(int x, int y, int width, int height, bool isPermanent)
{
	c.paint.push_back("fillOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::drawString(string s, int x, int y, bool isPermanent)
{
	c.paint.push_back("drawString," + s + "," + to_string(x) + "," + to_string(y) + "," + to_string(isPermanent) + "," + instanceName);
}
void JComponent::drawPolygon(Polygon p)
{
	//do stuff with draw polygon
}
void JComponent::fillPolgon(Polygon p)
{
	//do stuff with fill polygon
}
void JComponent::repaint()
{
	file1.open("test1.csv");
	for (string s : c.paint)
	{
		file1 << s + "\n";
	}
	file1.close(); //might need to move this to finish()
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
	void pause(double ld);
	ofstream file;
	ofstream file1;
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
	file1.open("test1.csv");
	file.clear();
	file1.clear();

	file << "removeAll \n";

	//might need to move this to finish()
	file1.close();
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
void Cpp2Java::pause(double ld)
{
	typedef std::chrono::duration<double> seconds_type;
	seconds_type period(ld);
	this_thread::sleep_for(period);
}

