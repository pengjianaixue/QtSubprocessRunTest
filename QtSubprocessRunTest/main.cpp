#include "qtsubprocessruntest.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
	//AllocConsole();
	QApplication a(argc, argv);
	QApplication::setStyle("Fusion");
	QtSubprocessRunTest w;
	w.show();
	return a.exec();
}
