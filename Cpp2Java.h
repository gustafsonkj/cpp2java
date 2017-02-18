// Test_Interface.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>

using namespace std;

class Commands
{
public:
	vector<string> gui;
	vector<string> paint;
	int instanceCounter;
};
Commands c;

class Polygon
{
public:
	void addPoint(int x, int y);
	pair<int, int> point;
	vector<pair<int, int>> coord;
};
void Polygon::addPoint(int x, int y)
{
	point = make_pair(x, y);
	coord.push_back(point);
}

class JComponent
{
	friend class Cpp2Java;
	friend class Polygon;
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
	c.gui.push_back("add," + instanceName + "," + jc.instanceName);
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
	string line;
	line = "drawPolygon";
	for (pair<int, int> pr : p.coord)
	{
		line += "," + to_string(pr.first) + "*" + to_string(pr.second);
	}
	c.paint.push_back(line);

}
void JComponent::fillPolgon(Polygon p)
{
	string line;
	line = "fillPolygon";
	for (pair<int, int> pr : p.coord)
	{
		line += "," + to_string(pr.first) + "*" + to_string(pr.second);
	}
	c.paint.push_back(line);
}
void JComponent::repaint()
{
	file1.open("test1.csv");
	for (string s : c.paint)
	{
		file1 << s + "\n";
	}
	file1.close();
	//might need to add signal file in case of race condition
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
	c.gui.push_back("instantiate,JPanel," + instanceName);
}

class JLabel : public JComponent
{
public:
	JLabel(string s);
	JLabel(string s, int alignment);
	//JLabel(Icon image);
	void setText(string s);
};
JLabel::JLabel(string s)
{
	setInstanceName();
	c.gui.push_back("instantiate,JLabel," + s + "," + instanceName);
}
JLabel::JLabel(string s, int alignment)
{
	setInstanceName();
	c.gui.push_back("instantiate,JLabel," + s + "," + to_string(alignment) + "," + instanceName);
}
void JLabel::setText(string s)
{
	c.gui.push_back("setText," + s + "," + instanceName);
}

class JTextField : public JComponent
{
public:
	JTextField(string text, int numCol);
	JTextField(int numCol);
	void setEditable(bool mode);
	void setText(string newText);
};
JTextField::JTextField(string text, int numCol)
{
	setInstanceName();
	c.gui.push_back("instantiate,JTextField," + text + "," + to_string(numCol) + "," + instanceName);
}
JTextField::JTextField(int numCol)
{
	setInstanceName();
	c.gui.push_back("instantiate,JTextField," + to_string(numCol) + "," + instanceName);
}
void JTextField::setEditable(bool mode)
{
	c.gui.push_back("setEditable," + to_string(mode) + "," + instanceName);
}
void JTextField::setText(string newText)
{
	c.gui.push_back("setText," + newText + "," + instanceName);
}

class JButton : public JComponent
{
public:
	JButton();
	JButton(string text);
	void addActionListener(); 
};
JButton::JButton()
{
	setInstanceName();
	c.gui.push_back("instantiate,JButton,"+instanceName);
}
JButton::JButton(string text)
{
	setInstanceName();
	c.gui.push_back("instantiate,JButton,"+ text+","+instanceName);
}

void JButton::addActionListener()
{

}

class JTextArea : public JComponent
{
public:
	JTextArea(string text);
	JTextArea(int numRows, int numCol);
	JTextArea(string text, int numRows, int numCol);
	void setEditable(bool mode);
	void setText(string newText);
};
JTextArea::JTextArea(string text)
{
	setInstanceName();
	c.gui.push_back("instantiate,JTextArea," + text + "," + instanceName);
}
JTextArea::JTextArea(int numRows, int numCol)
{
	setInstanceName();
	c.gui.push_back("instantiate,JTextArea," + to_string(numRows) + "," + to_string(numCol) + "," + instanceName);
}
JTextArea::JTextArea(string text, int numRows, int numCol)
{
	setInstanceName();
	c.gui.push_back("instantiate,JTextArea," + text + "," + to_string(numRows) + "," + to_string(numCol) + "," + instanceName);
}
void JTextArea::setEditable(bool mode)
{
	c.gui.push_back("setEditable," + to_string(mode) + "," + instanceName);
}
void JTextArea::setText(string newText)
{
	c.gui.push_back("setText," + newText + "," + instanceName);
}

class Cpp2Java
{
public:
	Cpp2Java();
	void removeAll();
	void finish();
	void setLayout(string s);
	void setLayout(string gridLayout, int numRows, int numCol);
	void setLayout(string gridLayout, int numRows, int numCol, int hGap, int wGap);
	void setLayout(string borderLayout, int hGap, int wGap);
	void pause(double ld);
	ofstream file;
	ofstream file1;

};
Cpp2Java::Cpp2Java()
{

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
	for (string s : c.gui)
	{
		file << s + "\n";
	}
	file << "end" << endl;
	file.close();
}
//temporary layout functions
//may need to change layouts to objects
void Cpp2Java::setLayout(string  s) //for flowLayout and default borderLayout
{
	c.gui.push_back("setLayout," + s);
}
void Cpp2Java::setLayout(string gridLayout, int numRows, int numCol) //for gridLayout
{
	c.gui.push_back("setLayout," + gridLayout + "," + to_string(numRows) + "," + to_string(numCol));
}
void Cpp2Java::setLayout(string gridLayout, int numRows, int numCol, int hGap, int wGap) //for gridLayout
{
	c.gui.push_back("setLayout," + gridLayout + "," + to_string(numRows) + "," + to_string(numCol) + "," + to_string(hGap) + "," + to_string(wGap));
}
void Cpp2Java::setLayout(string borderLayout, int hGap, int wGap) //for borderLayout with gaps
{
	c.gui.push_back("setLayout," + borderLayout + "," + to_string(hGap) + "," + to_string(wGap));
}
void Cpp2Java::pause(double ld)
{
	typedef std::chrono::duration<double> seconds_type;
	seconds_type period(ld);
	this_thread::sleep_for(period);
}


