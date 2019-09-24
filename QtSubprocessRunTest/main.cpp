#include "qtsubprocessruntest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtSubprocessRunTest w;
	w.show();
	return a.exec();
}
