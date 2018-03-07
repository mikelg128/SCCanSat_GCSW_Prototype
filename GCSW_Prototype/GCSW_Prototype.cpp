//source file for the main window class

//preprocessor definitions
#define DEBUG_ON 1 //Debugger on if == 1; currently does not actually do anything
#define FILE_EXTENSION ".txt" //sets the file extension; in the future we want to write to .csv files, but need to implement commas for that

#include "GCSW_Prototype.h"
#include <qdebug.h> //probably don't include debugger messages in final version. Use preprocessor commands? 


GCSW_Prototype::GCSW_Prototype(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	setSerialPort();	//Sets up and opens Serial port. Replace later with GUI dialogue
	isWriting = false;	//Init 
	isNamed = false;	//Init
	ui.fileNameField->setPlaceholderText("Enter your file name here");	//Place holder for file name field

	//By default all buttons are disabled
	ui.setFileNameButton->setEnabled(false);	//will enable when text written to field
	ui.startButton->setEnabled(false);			//will enable when fileName is saved
	ui.stopButton->setEnabled(false);			//will enable when writing

	//Connection definitions
	GCSW_Prototype::connect(&GCSWSerialPort, &QSerialPort::readyRead, this, &GCSW_Prototype::readSerialPort);	//Connects read slot function
	GCSW_Prototype::connect(ui.setFileNameButton, &QPushButton::pressed, this, &GCSW_Prototype::newFileName);	//Connects setFileNameButton to set slot
	GCSW_Prototype::connect(ui.startButton, &QPushButton::pressed, this, &GCSW_Prototype::startWriting);		//Connects startButton to startWriting slot
	GCSW_Prototype::connect(ui.stopButton, &QPushButton::pressed, this, &GCSW_Prototype::stopWriting);			//Connects stopButton to stopWriting slot
	GCSW_Prototype::connect(ui.fileNameField, &QLineEdit::textEdited, this, &GCSW_Prototype::setFNButtonState);	//Monitors text field
}


////////////////////////////////////////////////////////////////PUBLIC FUNCTIONS/////////////////////////////////////////////////////////////////////


void GCSW_Prototype::setSerialPort()	//setup function for serial port
{
	QSerialPortInfo *GCSWSerialPortInfo = new QSerialPortInfo();	//Helper class for serial ports
	QList<QSerialPortInfo> SerialList = GCSWSerialPortInfo->availablePorts(); //Lists available ports
#if DEBUG_ON == 1													//just because
	qDebug() << "Serial Port Info:";
	for (int i = 0; i < SerialList.size(); ++i) {					//print list to debugger
		qDebug() << SerialList.at(i).description();
		qDebug() << SerialList.at(i).portName();
	}
#endif
	int port = 1;													//manually selected port from debugger list. Will implement a way to do this through GUI
	GCSWSerialPort.setPort(SerialList.at(port));					//Sets port
	qDebug() << "Selected Port: " << GCSWSerialPort.portName();		//replace later? 
	GCSWSerialPort.setBaudRate(9600);								//set Baud Rate. There's probaably other settings I should worry about. 
	if (GCSWSerialPort.open(QIODevice::ReadWrite)) {				//Conditional that opens the port and checks for success
		qDebug() << "Port successfully opened";						//replace later? 
	}
	else {
		qDebug() << "Error: Unable to open port";
	}
}

void GCSW_Prototype::setFileName(QString newName) //setter for fileName private member
{
	fileName = newName + FILE_EXTENSION;	//sets fileName to passed QString and adds the file extension
	qDebug() << "File Name: " << fileName;
	file.setFileName(fileName);				//sets file name for the class instance of QFile
	isNamed = true;							//Class now knows that the file has been named
	this->ui.startButton->setEnabled(true);	//Enables button now that the file name is saved
}

void GCSW_Prototype::writeToFile(QString serialData) //called in the readSerialPort function if writing is enabled
{
	fout << serialData << endl;		//Writes serial data to file
}


//////////////////////////////////////////////////////////////////////SLOTS//////////////////////////////////////////////////////////////////////////


void GCSW_Prototype::readSerialPort() //if the readReady signal is received, this function activates
{
	qDebug() << "readSerialPort() activated";
	QString newData = GCSWSerialPort.readAll();		//Simplistic way to do this. Didn't use the buffer. Might not be great for fast data. 
	this->ui.textBrowser->append(newData);			//Pushes data to GUI
	if (isWriting == true & file.isOpen())			//Checks if writing is enabled
	{
		writeToFile(newData);						//Writes incoming data to file if writing is enabled
	}
}

void GCSW_Prototype::setFNButtonState() //called when text in field is edited
{
	qDebug() << "setFNButtonState() Activated";
	if (this->ui.fileNameField->text() == "")			//Checks for text in the field
	{
		this->ui.setFileNameButton->setEnabled(false);	//deactivates button if no text in the field
		qDebug() << "setFileNameButton disabled";
	}
	else
	{
		this->ui.setFileNameButton->setEnabled(true);	//activates button when text exists in the field
		qDebug() << "setFileNameButton enabled";
	}
}

void GCSW_Prototype::newFileName() //Activated when setFileNameButton is pressed
{
	qDebug() << "newFileName() activated";
	setFileName(this->ui.fileNameField->text()); //Read text field and save to a string
}

void GCSW_Prototype::startWriting() //Activated when startButton is pressed
{
	if (isNamed == true & isWriting == false) //Checks if fileName exists + if already writing; gray out button if already writing?
	{
		if (file.open(QIODevice::ReadWrite|QIODevice::Text)) //Maybe implement a check later for overwrite? 
		{
			isWriting = true;								//Class now knows that it is writing to a file
			qDebug() << "File '" << fileName << "' opened successfully";

			//Button control
			this->ui.startButton->setEnabled(false);		//disables start button now that file writing has started
			this->ui.fileNameField->setEnabled(false);		//disables text field while file is opened
			this->ui.setFileNameButton->setEnabled(false);	//disables set button while file is opened
			this->ui.stopButton->setEnabled(true);			//enables stop button now that the file is being written to
			fout.setDevice(&file);							//sets up the class QTextStream instance to write to the currently defined file
		}
		else
		{
			qDebug() << "File '" << fileName << "' could not be opened"; 
		}
	}
	else
	{
		qDebug() << "File name not set";
	}
}

void GCSW_Prototype::stopWriting() //Activated when stopButton is pressed 
{
	if (isWriting == true & file.isOpen())	//first checks if file writing was already active; maybe gray out button when not writing
	{
		isWriting = false;					//Class now knows that it is no longer writing to a file
		fout.flush();						//Flushes any remaining data in the text stream
		file.close();						//closes file
		qDebug() << "File closed";

		//Button control
		this->ui.startButton->setEnabled(true);		//enables start button now that writing is stopped
		this->ui.fileNameField->setEnabled(true);	//enables text field now that writing is stopped
		this->ui.setFileNameButton->setEnabled(true); //enables set button now that writing is stopped
		this->ui.stopButton->setEnabled(false);		//disables stop button now that writing is stopped
	}
	else
	{
		qDebug() << "File not open";
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GCSW_Prototype::~GCSW_Prototype() //Deconstructor to close any open IODevices
{
	if (GCSWSerialPort.isOpen())
	{
		GCSWSerialPort.close();
		qDebug() << "Serial port closed on program exit";
	}
	if (file.isOpen())
	{
		file.close();
		fout.flush();
		qDebug() << "File closed on program exit";
	}
}