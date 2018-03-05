#include "GCSW_Prototype.h"
#include <qdebug.h> //probably don't include debugger messages in final version. look into precompiler commands for this. 


GCSW_Prototype::GCSW_Prototype(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	QTextBrowser *tb; //Initializes text browser in GUI. Should this be here? 
	QScrollBar *sb; //artifact from messing w/ scrollbar.. remove later maybe
	tb = ui.textBrowser; //for ease of writing to text browser
	
	tb->setPlainText("Start serial port debugging"); //Initial message
	setSerialPort(); //Sets up and opens Serial port
	
	GCSW_Prototype::connect(&GCSWSerialPort, &QSerialPort::readyRead, this, &GCSW_Prototype::readSerialPort); //Connects read slot function
}

void GCSW_Prototype::setSerialPort() //setup function for serial port
{
	QSerialPortInfo *GCSWSerialPortInfo = new QSerialPortInfo(); //Helper class for serial ports
	qDebug() << "Serial Port Info:";
	QList<QSerialPortInfo> SerialList = GCSWSerialPortInfo->availablePorts(); //Lists available ports
	for (int i = 0; i < SerialList.size(); ++i) { //print list to debugger
		qDebug() << SerialList.at(i).description();
		qDebug() << SerialList.at(i).portName();
	}
	int port = 1; //manually selected port from debugger list. Will implement a way to do this through GUI
	GCSWSerialPort.setPort(SerialList.at(port)); //Sets port
	qDebug() << "Selected Port: " << GCSWSerialPort.portName();
	GCSWSerialPort.setBaudRate(9600); //set Baud Rate. There's probaably other settings I should worry about. 
	if (GCSWSerialPort.open(QIODevice::ReadWrite)) { //Conditional that opens the port and checks for success
		qDebug() << "Port successfully opened";
	}
	else {
		qDebug() << "Error: Unable to open port";
	}


	//system("PAUSE");
}

void GCSW_Prototype::readSerialPort() //if the readReady signal is received, this function activates
{
	qDebug() << "readSerialPort() activated";
	QString newData = GCSWSerialPort.readAll(); //Simplistic way to do this. Didn't use the buffer. Might not be great for fast data. 
	this->ui.textBrowser->append(newData); //Pushes data to GUI
}

GCSW_Prototype::~GCSW_Prototype() //Deconstructor to close serial port
{
	if (GCSWSerialPort.isOpen())
	{
		GCSWSerialPort.close();
	}
	qDebug() << "Serial port closed";
}