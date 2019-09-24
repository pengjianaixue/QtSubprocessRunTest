#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtsubprocessruntest.h"

class QtSubprocessRunTest : public QMainWindow
{
	Q_OBJECT

public:
	QtSubprocessRunTest(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtSubprocessRunTestClass ui;
};
