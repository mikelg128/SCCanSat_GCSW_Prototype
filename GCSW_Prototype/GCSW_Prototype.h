#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GCSW_Prototype.h"

class GCSW_Prototype : public QMainWindow
{
	Q_OBJECT

public:
	GCSW_Prototype(QWidget *parent = Q_NULLPTR);

private:
	Ui::GCSW_PrototypeClass ui;
};
