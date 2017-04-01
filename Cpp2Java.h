// Test_Interface.cpp : Defines the entry point for the console application.
//
#ifndef CPP2JAVA_H
#define CPP2JAVA_H
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <utility>
//#include "FileWatcher.h"
#include <stdexcept>

using namespace std;

class Commands {
public:
	vector<string> gui;
	vector<string> paint;
	int instanceCounter;
};
Commands c;

class KeyEvent {
public:
	KeyEvent(char keyPressed);
	char getKeyChar();
private:
	char key;
};
KeyEvent::KeyEvent(char keyPressed)
{
	key = keyPressed;
}
char KeyEvent::getKeyChar()
{
	return key;
}
class KeyListener {
public:
	virtual void keyReleased(KeyEvent ke) {};
};

class Polygon {
public:
	void addPoint(int x, int y);
	pair<int, int> point;
	vector<pair<int, int> > coord;
};
void Polygon::addPoint(int x, int y)
{
	point = make_pair(x, y);
	coord.push_back(point);
}

class Image {
public:
	Image(string file);
	string filename;
};
Image::Image(string file)
{
	filename = file;
}

class LayoutManager {
private:
	string type;

public:
	void setLayoutType(string type_in);
	string getLayoutType();
};
string LayoutManager::getLayoutType()
{
	return type;
}
void LayoutManager::setLayoutType(string type_in)
{
	type = type_in;
}

class BorderLayout : public LayoutManager {
public:
	BorderLayout();
	BorderLayout(int hGap, int vGap);
	int verticalGap;
	int horizontalGap;
};
BorderLayout::BorderLayout() //0
{
	setLayoutType("BorderLayout,0");
}
BorderLayout::BorderLayout(int hGap, int vGap) //1
{
	setLayoutType("BorderLayout,1");
	verticalGap = vGap;
	horizontalGap = hGap;
}

class GridLayout : public LayoutManager {
public:
	GridLayout(int numberOfRows, int numberOfColumns);
	GridLayout(int numberOfRows, int numberOfColumns, int hGap, int vGap);
	int numRows;
	int numCols;
	int horzontalGap;
	int verticalGap;
};
GridLayout::GridLayout(int numberOfRows, int numberOfColumns)
{
	setLayoutType("GridLayout,0");
	numRows = numberOfRows;
	numCols = numberOfColumns;
}
GridLayout::GridLayout(int numberOfRows, int numberOfColumns, int hGap, int vGap)
{
	setLayoutType("GridLayout,1");
	numRows = numberOfRows;
	numCols = numberOfColumns;
	horzontalGap = hGap;
	verticalGap = vGap;
}

class JComponent {
	friend class Cpp2Java;
	friend class Polygon;

public:
	JComponent() {};
	JComponent(const JComponent & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JComponent& jC);
	void operator = (JComponent & jC)
	{
		instanceName = jC.instanceName;
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->instanceName;
	}
	virtual void add(JComponent& jc);
	virtual void drawRect(int x, int y, int width, int height);
	virtual void drawLine(int xStart, int yStart, int xEnd, int yEnd);
	virtual void fillRect(int x, int y, int width, int height);
	virtual void clearRect(int x, int y, int width, int height);
	virtual void drawOval(int x, int y, int width, int height);
	virtual void fillOval(int x, int y, int width, int height);
	virtual void drawPolygon(Polygon p);
	virtual void fillPolgon(Polygon p);
	virtual void drawString(string s, int x, int y);
	virtual void drawImage(Image & i, int x, int y);
	virtual void drawImage(Image * i, int x, int y);
	virtual void setColor(string color);
	virtual void setForeground(string color);
	virtual void setBackground(string color);
	virtual void repaint();
	string getInstanceName();
	ofstream file1;
	string instanceName;

protected:
	void setInstanceName();
};
/*ostream& operator<<(ostream& os, JComponent& jC)
{
os << "InstanceName:" << jC.instanceName;
return os;
}*/
ostream& operator<<(ostream& os, JComponent* jC)
{
	os << "InstanceName:" << jC->instanceName;
	return os;
}
ostream& operator<<(ostream& os, JComponent jC)
{
	os << "InstanceName:" << jC.instanceName;
	return os;
}
bool JComponent::operator==(JComponent & jC)
{
	return instanceName.compare(jC.instanceName) == 0;
};
void JComponent::add(JComponent& jc)
{
	c.gui.push_back(instanceName + ",add," + jc.instanceName);
}
void JComponent::drawRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",drawRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawLine(int xStart, int yStart, int xEnd, int yEnd)
{
	c.paint.push_back(instanceName + ",drawLine," + to_string(xStart) + "," + to_string(yStart) + "," + to_string(xEnd) + "," + to_string(yEnd));
}
void JComponent::fillRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",fillRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::clearRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",clearRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawOval(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",drawOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::fillOval(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + ",fillOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawString(string s, int x, int y)
{
	c.paint.push_back(instanceName + ",drawString," + s + "," + to_string(x) + "," + to_string(y));
}
void JComponent::drawPolygon(Polygon p)
{
	string line;
	line = instanceName + ",drawPolygon";
	for (pair<int, int> pr : p.coord) {
		line += "," + to_string(pr.first) + "*" + to_string(pr.second);
	}
	c.paint.push_back(line);
}
void JComponent::fillPolgon(Polygon p)
{
	string line;
	line = instanceName + "fillPolygon";
	for (pair<int, int> pr : p.coord) {
		line += "," + to_string(pr.first) + "*" + to_string(pr.second);
	}
	c.paint.push_back(line);
}
void JComponent::drawImage(Image & i, int x, int y)
{
	c.paint.push_back(instanceName + ",drawImage," + i.filename + "," + to_string(x) + "," + to_string(y));
}
void JComponent::drawImage(Image * i, int x, int y)
{
	c.paint.push_back(instanceName + ",drawImage," + i->filename + "," + to_string(x) + "," + to_string(y));
}
void JComponent::setColor(string color)
{
	c.paint.push_back(instanceName + ",setColor," + color);
}
void JComponent::setForeground(string color)
{
	c.gui.push_back(instanceName + ",setForeground," + color);
}
void JComponent::setBackground(string color)
{
	c.gui.push_back(instanceName + ",setBackground," + color);
}
void JComponent::repaint()
{
	file1.open("Cpp2Java_paint.csv");
	for (string s : c.paint) {
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
string JComponent::getInstanceName()
{
	return instanceName;
}

// This vector is used to reference action events.
// It must be declared after JComponent is defined.

vector<JComponent> jComps;


//
//


class ActionEvent
{
public:
	ActionEvent(int jc);
	JComponent getSource();
	int jC;
};

ActionEvent::ActionEvent(int jc)
{
	jC = jc;
}
JComponent ActionEvent::getSource()
{
	return (jComps[jC]);
}

class ActionListener
{
public:
	ActionListener() {};
	ActionListener(const ActionListener & copy) {};
	virtual void actionPerformed(ActionEvent ae);
	virtual void actionPerformed(ActionEvent * ae) {};
};
void ActionListener::actionPerformed(ActionEvent ae)
{}

class JPanel : public JComponent {
public:
	JPanel();
	void setLayout(GridLayout* gl);
	void setLayout(BorderLayout* bl);
	void add(JComponent& jc);
	void add(JComponent& jc, string layout);
};
JPanel::JPanel() //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JPanel");
	jComps.push_back(*this);
}
void JPanel::setLayout(GridLayout* gl)
{
	if (gl->getLayoutType() == "GridLayout,0")
		c.gui.push_back(instanceName + ",setLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols));
	else
		c.gui.push_back(instanceName + ",setLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols) + "," + to_string(gl->horzontalGap) + "," + to_string(gl->verticalGap));
}
void JPanel::setLayout(BorderLayout* bl)
{
	if (bl->getLayoutType() == "BorderLayout,0")
		c.gui.push_back(instanceName + ",setLayout," + bl->getLayoutType());
	else
		c.gui.push_back(instanceName + ",setLayout," + bl->getLayoutType() + "," + to_string(bl->horizontalGap) + "," + to_string(bl->verticalGap));
}
void JPanel::add(JComponent& jc)
{
	c.gui.push_back(instanceName + ",add," + jc.getInstanceName());
}
void JPanel::add(JComponent& jc, string layout)
{
	c.gui.push_back(instanceName + ",add," + jc.getInstanceName() + "," + layout);
}

class JLabel : public JComponent {
public:
	JLabel(string s);
	JLabel(string s, int alignment);
	JLabel(Image image);
	void setText(string s);
};
JLabel::JLabel(string s) //0
{
	setInstanceName();
	string n;
	for (char i : s)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,0,JLabel," + n);
	jComps.push_back(*this);

}
JLabel::JLabel(string s, int alignment) //1
{
	setInstanceName();
	string n;
	for (char i : s)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,1,JLabel," + n + "," + to_string(alignment));
	jComps.push_back(*this);
}
JLabel::JLabel(Image image)
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instance,2,JLabel," + image.filename);
	jComps.push_back(*this);
}
void JLabel::setText(string s)
{
	string n;
	for (char i : s)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",setTextJL," + n);
}

class JTextField : public JComponent {
public:
	JTextField(JTextField & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JTextField & jtf)
	{
		return instanceName.compare(jtf.instanceName) == 0;
	}
	bool operator==(JComponent & jC)
	{
		return instanceName.compare(jC.getInstanceName()) == 0;
	}
	void operator = (JComponent & jC)
	{
		instanceName = jC.getInstanceName();
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->getInstanceName();
	}
	JTextField(string text, int numCol);
	JTextField(int numCol);
	void setEditable(bool mode);
	void setText(string newText);
	void addActionListener(ActionListener * aL);
	void addActionListener(ActionListener & aL);
};
JTextField::JTextField(string text, int numCol) //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JTextField," + text + "," + to_string(numCol));
	jComps.push_back(*this);
}
JTextField::JTextField(int numCol) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JTextField," + to_string(numCol));
	jComps.push_back(*this);
}
void JTextField::setEditable(bool mode)
{
	c.gui.push_back(instanceName + ",setEditable," + to_string(mode));
}
void JTextField::setText(string newText)
{
	string n;
	for (char i : newText)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",setTextJTF," + n);
}
void JTextField::addActionListener(ActionListener * aL)
{
	c.gui.push_back(instanceName + ",addActionListener");

}
void JTextField::addActionListener(ActionListener & aL)
{
	c.gui.push_back(instanceName + ",addActionListener");

}

class JButton : public JComponent {
public:
	JButton(JButton & copy) {
		instanceName = copy.instanceName;
	};
	bool operator==(JButton & jB)
	{
		return instanceName.compare(jB.instanceName) == 0;
	}
	bool operator==(JComponent & jC)
	{
		return instanceName.compare(jC.getInstanceName()) == 0;
	}
	void operator = (JComponent & jC)
	{
		instanceName = jC.getInstanceName();
	}
	void operator = (JComponent * jC)
	{
		instanceName = jC->getInstanceName();
	}
	JButton();
	JButton(string text);
	void addActionListener(ActionListener * aL);
	void addActionListener(ActionListener & aL);
};
JButton::JButton() //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JButton");
	jComps.push_back(*this);

}
JButton::JButton(string text) //1
{
	setInstanceName();
	string n;
	for (char i : text)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,1,JButton,"+n);
	jComps.push_back(*this);

}
void JButton::addActionListener(ActionListener * aL)
{
	c.gui.push_back(instanceName + ",addActionListener");
}
void JButton::addActionListener(ActionListener & aL)
{
	c.gui.push_back(instanceName + ",addActionListener");
}

class JTextArea : public JComponent {
public:
	JTextArea(string text);
	JTextArea(int numRows, int numCol);
	JTextArea(string text, int numRows, int numCol);
	void setEditable(bool mode);
	void setText(string newText);
};
JTextArea::JTextArea(string text) //0
{
	setInstanceName();
	string n;
	for (char i : text)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,0,JTextArea," + n);
	jComps.push_back(*this);
}
JTextArea::JTextArea(int numRows, int numCol) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JTextArea," + to_string(numRows) + "," + to_string(numCol));
	jComps.push_back(*this);
}
JTextArea::JTextArea(string text, int numRows, int numCol) //2
{
	setInstanceName();
	string n;
	for (char i : text)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",instantiate,2,JTextArea," + n + "," + to_string(numRows) + "," + to_string(numCol));
	jComps.push_back(*this);
}
void JTextArea::setEditable(bool mode)
{
	c.gui.push_back(instanceName + ",setEditable," + to_string(mode));
}
void JTextArea::setText(string newText)
{
	string n;
	for (char i : newText)
		if (i != ',')
			n += i;
	c.gui.push_back(instanceName + ",setTextJTA," + n);
}

class Cpp2Java {
public:
	Cpp2Java();
	void removeAll();
	void finish();
	void pause(double ld);
	void setLayout(GridLayout* gl);
	void setLayout(BorderLayout* bl);
	void addKeyListener(KeyListener * kL);
	void addKeyListener(KeyListener & kL);
	void add(JComponent& jc);
	void add(JComponent& jc, string layout);
	ofstream file;
	ofstream file1;

private:
	KeyListener * storedKL = new KeyListener();
};
Cpp2Java::Cpp2Java()
{
};
void Cpp2Java::removeAll()
{
	file.open("Cpp2Java_gui.csv");
	file.clear();
	file << "-1,removeAll\n";

	//might need to move this to finish()
}
void Cpp2Java::finish()
{
	for (string s : c.gui) {
		file << s + "\n";
	}
	file << "-1,end" << endl;
	file.close();

	// LOOP PHASE
	struct stat st;
	int ierr = stat("test.txt", &st); // FILE TO BE WATCHED
	if (ierr != 0) {
		cout << "error";
	}
	int date = st.st_mtime;
	while (1) {
		ierr = stat("test.txt", &st); // FILE TO BE WATCHED
		int newdate = st.st_mtime;

		this_thread::sleep_for(chrono::milliseconds(100));

		if (newdate == date) {
			// DO NOTHING
		}
		else if (newdate != date) {
			date = newdate; // IMPORTANT

			string command;
			ifstream infile;
			infile.open("Java2Cpp.csv");
			while (!infile.eof()) // To get you all the lines.
			{
				getline(infile, command); // Saves the line in STRING.
				//cout << command; // Prints our STRING.
			}
			infile.close();

			string delimiter = ",";

			size_t pos = 0;
			string token;
			vector<string> JavaCommand;
			while ((pos = command.find(delimiter)) != string::npos) {
				token = command.substr(0, pos);
				JavaCommand.push_back(token);
				command.erase(0, pos + delimiter.length());
			}
			
			switch (stoi(JavaCommand.at(0)))
			{
			case -1:
				if (JavaCommand.at(1).compare("KeyEvent")) //Key Listeners
				{
					// Use Java Command vector to call commands here
					storedKL.keyReleased(*new KeyEvent(JavaCommand.at(2).at(0)));
				}
				else if (JavaCommand.at(1).compare("MouseEvent")) //Mouse Listeners
				{

				}
				else if (JavaCommand.at(1).compare("MouseMotionEvent")) //Mouse Motion Listeners
				{

				}
				break;
			case 0:
				//Action Listeners
				break;
			case 1:
				//Item Listeners
				break;
			default:
				break;
			}

		}
	}

}
/*void Cpp2Java::pause(double ld)
{
	typedef std::chrono::duration<double> seconds_type;
	if (ld > .01)
	{
		seconds_type period(ld);
		this_thread::sleep_for(period);
	}
	else
	{
		seconds_type period(.01);
		this_thread::sleep_for(period);
	}
}*/
void Cpp2Java::setLayout(GridLayout* gl)
{
	if (gl->getLayoutType() == "GridLayout,0")
		c.gui.push_back("-1,setContainerLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols));
	else
		c.gui.push_back("-1,setContainerLayout," + gl->getLayoutType() + "," + to_string(gl->numRows) + "," + to_string(gl->numCols) + "," + to_string(gl->horzontalGap) + "," + to_string(gl->verticalGap));
}
void Cpp2Java::setLayout(BorderLayout* bl)
{
	if (bl->getLayoutType() == "BorderLayout,0")
		c.gui.push_back("-1,setContainerLayout," + bl->getLayoutType());
	else
		c.gui.push_back("-1,setContainerLayout," + bl->getLayoutType() + "," + to_string(bl->horizontalGap) + "," + to_string(bl->verticalGap));
}
void Cpp2Java::addKeyListener(KeyListener * kL)
{
	c.gui.push_back("-1,addKeyListener");

	storedKL = kL;
}
void Cpp2Java::addKeyListener(KeyListener & kL)
{
	c.gui.push_back("-1,addKeyListener");

	storedKL = &kL;
}
void Cpp2Java::add(JComponent& jc)
{
	c.gui.push_back("-1,addContainer," + jc.getInstanceName());
}
void Cpp2Java::add(JComponent& jc, string layout)
{
	c.gui.push_back("-1,addContainer," + jc.getInstanceName() + "," + layout);
}

#endif // !CPP2JAVA_H