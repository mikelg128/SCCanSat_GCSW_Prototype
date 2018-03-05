#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GCSW_Prototype.h"
#include <qserialport.h>
#include <qserialportinfo.h>

namespace Ui {
	class GCSW_Prototype;
}

class GCSW_Prototype : public QMainWindow
{
	Q_OBJECT

public:
	GCSW_Prototype(QWidget *parent = Q_NULLPTR);
	~GCSW_Prototype();
	void setSerialPort();

public slots:
	void readSerialPort();

private:
	char buffer[50]; //currently not used
	Ui::GCSW_PrototypeClass ui;
	QSerialPort GCSWSerialPort;
	
};
