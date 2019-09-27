#include "qtsubprocessruntest.h"

QtSubprocessRunTest::QtSubprocessRunTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pyPath = QApplication::applicationDirPath() + "/test.py";
	connect(this->ui.pushButton_Start, &QPushButton::clicked, this, &QtSubprocessRunTest::startRunPyScript);
	connect(this->ui.pushButton_Stop, &QPushButton::clicked, this, &QtSubprocessRunTest::stopRunPyScript);
	connect(&this->m_subProcessRunner, &SubProcessRunner::signal_SendSubProcessStdoutContents, this, &QtSubprocessRunTest::displayPyStdoutToBorwse);
	connect(this->ui.pushButton_clean, &QPushButton::clicked, this, [&] {ui.textBrowser->clear(); });
}

void QtSubprocessRunTest::startRunPyScript()
{ 
	m_subProcessRunner.startRun(std::string("python -u ") +  R"(")" +  m_pyPath.toStdString() + R"(")");
}
QtSubprocessRunTest::~QtSubprocessRunTest()
{
	m_subProcessRunner.stop();
}
void QtSubprocessRunTest::stopRunPyScript()
{
	m_subProcessRunner.stop();

}

void QtSubprocessRunTest::displayPyStdoutToBorwse(const QString &stdoutcontents)
{
	QString stdoutcontent = stdoutcontents;
	stdoutcontent = stdoutcontent.replace(QRegExp("\r\n\r\n"),"\r\n");
	this->ui.textBrowser->append(stdoutcontent);
	this->ui.textBrowser->update();
}
