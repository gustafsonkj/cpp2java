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
#include <iostream>
#include <stdexcept>

namespace FW
{
	/// Type for a string
	typedef std::string String;
	/// Type for a watch id
	typedef unsigned long WatchID;

	// forward declarations
	class FileWatcherImpl;
	class FileWatchListener;

	/// Base exception class
	/// @class Exception
	class Exception : public std::runtime_error
	{
	public:
		Exception(const String& message)
			: std::runtime_error(message)
		{}
	};

	/// Exception thrown when a file is not found.
	/// @class FileNotFoundException
	class FileNotFoundException : public Exception
	{
	public:
		FileNotFoundException()
			: Exception("File not found")
		{}

		FileNotFoundException(const String& filename)
			: Exception("File not found (" + filename + ")")
		{}
	};

	/// Actions to listen for. Rename will send two events, one for
	/// the deletion of the old file, and one for the creation of the
	/// new file.
	namespace Actions
	{
		enum Action
		{
			/// Sent when a file is created or renamed
			Add = 1,
			/// Sent when a file is deleted or renamed
			Delete = 2,
			/// Sent when a file is modified
			Modified = 4
		};
	};
	typedef Actions::Action Action;

	/// Listens to files and directories and dispatches events
	/// to notify the parent program of the changes.
	/// @class FileWatcher
	class FileWatcher
	{
	public:
		///
		///
		FileWatcher();

		///
		///
		virtual ~FileWatcher();

		/// Add a directory watch
		/// @exception FileNotFoundException Thrown when the requested directory does not exist
		WatchID addWatch(const String& directory, FileWatchListener* watcher);

		/// Remove a directory watch. This is a brute force search O(nlogn).
		void removeWatch(const String& directory);

		/// Remove a directory watch. This is a map lookup O(logn).
		void removeWatch(WatchID watchid);

		/// Updates the watcher. Must be called often.
		void update();

	private:
		/// The implementation
		FileWatcherImpl* mImpl;

	};//end FileWatcher


	  /// Basic interface for listening for file events.
	  /// @class FileWatchListener
	class FileWatchListener
	{
	public:
		FileWatchListener() {}
		virtual ~FileWatchListener() {}

		/// Handles the action file action
		/// @param watchid The watch id for the directory
		/// @param dir The directory
		/// @param filename The filename that was accessed (not full path)
		/// @param action Action that was performed
		virtual void handleFileAction(WatchID watchid, const String& dir, const String& filename, Action action) = 0;

	};//class FileWatchListener

};//namespace FW

using namespace std;

class UpdateListener : public FW::FileWatcher {
public:
	UpdateListener() {};
	void handleFileAction(FW::WatchID watchID, const FW::String& dir, const FW::String& fileName, FW::Action action)
	{
		//put what occurs with actions here
		switch (action)
		{
		case FW::Actions::Add:
			//something is ADDED to the file
			break;
		case FW::Actions::Delete:
			//something is DELETED from the file
			break;
		case FW::Actions::Modified:
			//the file is CHANGED
			break;
		default:
			//this should never occur
			break;
		}
	}
	//This class is the basic file watching class. When an action is performed on the file specified, one of the specified action types is returned.
	//We will need to instantiate the following code in an area which will RUN: 
	//FW::FileWatcher fileWatcher;
	//FW::WatchID watchID = fileWatcher.addWatch("Cpp2Java_actionPerformed.csv", new UpdateListener());
	//We then need a loop running with the following code: 
	//fileWatcher.update()
	//This code will monitor all of the WatchIDs associated with it, checking for file changes.
	//Inside the interface folder is a file called "SimpleDemo", which is a demo of this file watcher's use. It includes the links to the source code online.
};

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

	bool operator==(const JComponent& jC)
	{
		return instanceName == jC.instanceName;
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

protected:
	void setInstanceName();
	string instanceName;
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
	c.gui.push_back(instanceName + ",instantiate,0,JLabel," + s);
}
JLabel::JLabel(string s, int alignment) //1
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instantiate,1,JLabel," + s + "," + to_string(alignment));
}
JLabel::JLabel(Image image)
{
	setInstanceName();
	c.gui.push_back(instanceName + ",instance,2,JLabel," + image.filename);
}
void JLabel::setText(string s)
{
	c.gui.push_back(instanceName + ",setTextJL," + s);
}

class JTextField : public JComponent {
public:
	JTextField(string text, int numCol);
	JTextField(int numCol);
	void setEditable(bool mode);
	void setText(string newText);
	void addActionListener();
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
void JTextField::addActionListener()
{
	c.gui.push_back(instanceName + ",addActionListener");
}

class JButton : public JComponent {
public:
	bool operator==( const JButton & jB)
	{
		return instanceName == jB.instanceName;
	}
	bool operator==( JComponent & jC)
	{
		return instanceName == jC.getInstanceName();
	}
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



// This vector is used to reference action events.
// It must be declared after JComponent is defined.

vector<JComponent> jComp;


//
//


class ActionEvent
{
public:
	ActionEvent(int jc);
	JComponent & getSource();
	int jC;
};

ActionEvent::ActionEvent(int jc)
{
	jC = jc;
}
JComponent & ActionEvent::getSource()
{
	return (jComp[jC]);
}

class ActionListener
{
public:
	void actionPerformed(ActionEvent ae);
};
void ActionListener::actionPerformed(ActionEvent ae)
{}

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
};

Cpp2Java::Cpp2Java()
{
}
void Cpp2Java::removeAll()
{
	file.open("Cpp2Java_gui.csv");
	file.clear();
	c.gui.clear();
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

	// WRITE CODE TO ADD THE KEY LISTENER TO A VECTOR FOR LATER REFERENCE
}
void Cpp2Java::addKeyListener(KeyListener & kL)
{
	c.gui.push_back("-1,addKeyListener");

	// WRITE CODE TO ADD THE KEY LISTENER TO A VECTOR FOR LATER REFERENCE
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