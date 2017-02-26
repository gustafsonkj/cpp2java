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

class LayoutManager
{
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

class BorderLayout : public LayoutManager
{
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

class GridLayout : public LayoutManager
{
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

class JComponent
{
	friend class Cpp2Java;
	friend class Polygon;
public:
	virtual void add(JComponent & jc);
	virtual void drawRect(int x, int y, int width, int height);
	virtual void drawLine(int xStart, int yStart, int xEnd, int yEnd);
	virtual void fillRect(int x, int y, int width, int height);
	virtual void clearRect(int x, int y, int width, int height);
	virtual void drawOval(int x, int y, int width, int height);
	virtual void fillOval(int x, int y, int width, int height);
	virtual void drawPolygon(Polygon p);
	virtual void fillPolgon(Polygon p);
	virtual void drawString(string s, int x, int y);
	virtual void repaint();
	string getInstanceName();
	ofstream file1;
protected:
	void setInstanceName();
	string instanceName;

};
void JComponent::add(JComponent & jc)
{
	c.gui.push_back(instanceName + ",add," + jc.instanceName);
}
void JComponent::drawRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + "drawRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawLine(int xStart, int yStart, int xEnd, int yEnd)
{
	c.paint.push_back(instanceName + "drawLine," + to_string(xStart) + "," + to_string(yStart) + "," + to_string(xEnd) + "," + to_string(yEnd));
}
void JComponent::fillRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + "fillRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::clearRect(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + "clearRect," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawOval(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + "drawOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::fillOval(int x, int y, int width, int height)
{
	c.paint.push_back(instanceName + "fillOval," + to_string(x) + "," + to_string(y) + "," + to_string(width) + "," + to_string(height));
}
void JComponent::drawString(string s, int x, int y)
{
	c.paint.push_back(instanceName + "drawString," + s + "," + to_string(x) + "," + to_string(y));
}
void JComponent::drawPolygon(Polygon p)
{
	string line;
	line = instanceName + "drawPolygon";
	for (pair<int, int> pr : p.coord)
	{
		line += "," + to_string(pr.first) + "*" + to_string(pr.second);
	}
	c.paint.push_back(line);

}
void JComponent::fillPolgon(Polygon p)
{
	string line;
	line = instanceName + "fillPolygon";
	for (pair<int, int> pr : p.coord)
	{
		line += "," + to_string(pr.first) + "*" + to_string(pr.second);
	}
	c.paint.push_back(line);
}
void JComponent::repaint()
{
	file1.open("paint.csv");
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
string JComponent::getInstanceName()
{
	return instanceName;
}

class JPanel : public JComponent
{
public:
	JPanel();
	void setLayout(GridLayout * gl);
	void setLayout(BorderLayout * bl);
	void add(JComponent & jc);
	void add(JComponent & jc, string layout);

};
JPanel::JPanel() //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JPanel");
}
void JPanel::setLayout(GridLayout * gl)
{
	if (gl->getLayoutType() == "GridLayout,0")
		c.gui.push_back(instanceName + ",setLayout," + gl->getLayoutType() + "," +
			to_string(gl->numRows) + "," + to_string(gl->numCols));
	else
		c.gui.push_back(instanceName + ",setLayout," + gl->getLayoutType() + "," +
			to_string(gl->numRows) + "," + to_string(gl->numCols) + "," + to_string(gl->horzontalGap) + "," + to_string(gl->verticalGap));
}
void JPanel::setLayout(BorderLayout * bl)
{
	if (bl->getLayoutType() == "BorderLayout,0")
		c.gui.push_back(instanceName + ",setLayout," + bl->getLayoutType());
	else
		c.gui.push_back(instanceName + ",setLayout," + bl->getLayoutType() + "," +
			to_string(bl->horizontalGap) + "," + to_string(bl->verticalGap));
}
void JPanel::add(JComponent & jc)
{
	c.gui.push_back(instanceName + ",add," + jc.getInstanceName());
}
void JPanel::add(JComponent & jc, string layout)
{
	c.gui.push_back(instanceName + ",add," + jc.getInstanceName() + "," + layout);
}

class JLabel : public JComponent
{
public:
	JLabel(string s);
	JLabel(string s, int alignment);
	//JLabel(Icon image);
	void setText(string s);
};
JLabel::JLabel(string s) //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JLabel," + s);
}
JLabel::JLabel(string s, int alignment) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JLabel," + s + "," + to_string(alignment));
}
void JLabel::setText(string s)
{
	c.gui.push_back(instanceName + ",setTextJL," + s);
}

class JTextField : public JComponent
{
public:
	JTextField(string text, int numCol);
	JTextField(int numCol);
	void setEditable(bool mode);
	void setText(string newText);
};
JTextField::JTextField(string text, int numCol) //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JTextField," + text + "," + to_string(numCol));
}
JTextField::JTextField(int numCol) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JTextField," + to_string(numCol));
}
void JTextField::setEditable(bool mode)
{
	c.gui.push_back(instanceName + ",setEditable," + to_string(mode));
}
void JTextField::setText(string newText)
{
	c.gui.push_back(instanceName + ",setTextJTF," + newText);
}

class JButton : public JComponent
{
public:
	JButton();
	JButton(string text);
	void addActionListener();
};
JButton::JButton() //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JButton");
}
JButton::JButton(string text) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JButton," + text);
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
JTextArea::JTextArea(string text) //0
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,0,JTextArea," + text);
}
JTextArea::JTextArea(int numRows, int numCol) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JTextArea," + to_string(numRows) + "," + to_string(numCol));
}
JTextArea::JTextArea(string text, int numRows, int numCol) //2
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,2,JTextArea," + text + "," + to_string(numRows) + "," + to_string(numCol));
}
void JTextArea::setEditable(bool mode)
{
	c.gui.push_back(instanceName + ",setEditable," + to_string(mode));
}
void JTextArea::setText(string newText)
{
	c.gui.push_back(instanceName + ",setTextJTA," + newText);
}

class Cpp2Java
{
public:
	Cpp2Java();
	void removeAll();
	void finish();
	void pause(double ld);
	void setLayout(GridLayout * gl);
	void setLayout(BorderLayout * bl);
	void add(JComponent & jc);
	void add(JComponent & jc, string layout);
	ofstream file;
	ofstream file1;

};
Cpp2Java::Cpp2Java()
{

}
void Cpp2Java::removeAll()
{
	file.open("text.csv");
	file.clear();
	c.gui.clear();
	file << "-1,removeAll\n";

	//might need to move this to finish()
}
void Cpp2Java::finish()
{
	for (string s : c.gui)
	{
		file << s + "\n";
	}
	file << "-1,end" << endl;
	file.close();
}
void Cpp2Java::pause(double ld)
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
}
void Cpp2Java::setLayout(GridLayout * gl)
{
	if (gl->getLayoutType() == "GridLayout,0")
		c.gui.push_back("-1,setContainerLayout," + gl->getLayoutType() + "," +
			to_string(gl->numRows) + "," + to_string(gl->numCols));
	else
		c.gui.push_back("-1,setContainerLayout," + gl->getLayoutType() + "," +
			to_string(gl->numRows) + "," + to_string(gl->numCols) + "," + to_string(gl->horzontalGap) + "," + to_string(gl->verticalGap));
}
void Cpp2Java::setLayout(BorderLayout * bl)
{
	if (bl->getLayoutType() == "BorderLayout,0")
		c.gui.push_back("-1,setContainerLayout," + bl->getLayoutType());
	else
		c.gui.push_back("-1,setContainerLayout," + bl->getLayoutType() + "," +
			to_string(bl->horizontalGap) + "," + to_string(bl->verticalGap));
}
void Cpp2Java::add(JComponent & jc)
{
	c.gui.push_back("-1,addContainer," + jc.getInstanceName());
}
void Cpp2Java::add(JComponent & jc, string layout)
{
	c.gui.push_back("-1,addContainer," + jc.getInstanceName() + "," + layout);
}

