#include "GCSW_Prototype.h"

GCSW_Prototype::GCSW_Prototype(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.textBrowser->setPlainText("Hello World");
}
