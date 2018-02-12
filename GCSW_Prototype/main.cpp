#include "GCSW_Prototype.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GCSW_Prototype w;
	w.show();
	return a.exec();
}
