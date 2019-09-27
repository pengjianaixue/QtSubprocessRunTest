#pragma once

#include <QtWidgets/QMainWindow>
#include "subProcessRunner.h"
#include "ui_qtsubprocessruntest.h"

class QtSubprocessRunTest : public QMainWindow
{
	Q_OBJECT

public:
	QtSubprocessRunTest(QWidget *parent = Q_NULLPTR);
	~QtSubprocessRunTest();
public slots:
	void startRunPyScript();
	void stopRunPyScript();
	void displayPyStdoutToBorwse(const QString &stdoutcontents);

private:
	Ui::QtSubprocessRunTestClass ui;
	SubProcessRunner		m_subProcessRunner;
	QString				    m_pyPath;
};
