#pragma once

#include <QtWidgets/QMainWindow>
#include "subProcessRunner.h"
#include "SubprocessRunnerWithSpawn.h"
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
	void pauseRunPyScript();
	void displayPyStdoutToBorwse(const QString &stdoutcontents);

private:
	Ui::QtSubprocessRunTestClass	ui;
	SubProcessRunner				m_subProcessRunner;
	SubprocessRunnerWithSpawn		m_subProcessRunnerWithSpawn;
	QString							m_pyPath;
};
