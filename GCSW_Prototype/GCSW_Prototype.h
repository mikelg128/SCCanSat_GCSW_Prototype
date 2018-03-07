//Header file for the main window class 

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GCSW_Prototype.h"
#include <qserialport.h>
#include <qserialportinfo.h>
#include <qfile.h>
#include <qtextstream.h>

namespace Ui {
	class GCSW_Prototype;
}

class GCSW_Prototype : public QMainWindow
{
	Q_OBJECT

public:
	GCSW_Prototype(QWidget *parent = Q_NULLPTR);//ctor
	~GCSW_Prototype();							//de-ctor
	void setSerialPort();						//sets up serial port
	void setFileName(QString newName);			//sets file name
	void writeToFile(QString serialData);		//writes to an open file

public slots:
	void readSerialPort();		//reads serial port
	void setFNButtonState();	//sets the state of the setFileName button
	void newFileName();			//grabs the new file name from the text field
	void startWriting();		//enables file writing
	void stopWriting();			//disables file writing

private: //probably not following good class conventions for private members (defining getters/setters and what not)
	char buffer[50];			//currently not used
	QString fileName;			//Holds the .csv/.txt file name
	Ui::GCSW_PrototypeClass ui; 
	QSerialPort GCSWSerialPort; //Serial port for the class; there may be a better way to implement this
	bool isWriting;				//Boolean that represents whether or not received data should be written to the open file
	bool isNamed;				//Boolean that represents whether or not the file has been named
	QFile file;					//file definition for the class
	QTextStream fout;			//Stream instance for the class; used to write to file
	
};
