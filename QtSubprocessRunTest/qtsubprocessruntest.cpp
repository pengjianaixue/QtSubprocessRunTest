#include "qtsubprocessruntest.h"

QtSubprocessRunTest::QtSubprocessRunTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	// 设置窗口背景颜色
	QPalette pal = window()->palette();
	pal.setColor(QPalette::Window, QRgb(0x018bba));
	pal.setColor(QPalette::WindowText, QRgb(0x018bba));
	pal.setColor(QPalette::ButtonText, QRgb(0x018bba));
	pal.setColor(QPalette::Light, QRgb(0x018bba));
	window()->setPalette(pal);
	pal = this->ui.pushButton_Start->window()->palette();
	pal.setColor(QPalette::Window, QRgb(0xd6d6d6));
	pal.setColor(QPalette::WindowText, QRgb(0x018bba));
	pal.setColor(QPalette::ButtonText, QRgb(0x018bba));
	this->ui.pushButton_Start->window()->setPalette(pal);
	m_pyPath = QApplication::applicationDirPath() + "/test.py";
	connect(this->ui.pushButton_Start, &QPushButton::clicked, this, &QtSubprocessRunTest::startRunPyScript);
	connect(this->ui.pushButton_Stop, &QPushButton::clicked, this, &QtSubprocessRunTest::stopRunPyScript);
	connect(&this->m_subProcessRunnerWithSpawn, &SubprocessRunnerWithSpawn::sigals_sendSubProcessOutput, this, &QtSubprocessRunTest::displayPyStdoutToBorwse);
	//connect(&this->m_subProcessRunner, &SubProcessRunner::signal_SendSubProcessStdoutContents, this, &QtSubprocessRunTest::displayPyStdoutToBorwse);
	connect(this->ui.pushButton_clean, &QPushButton::clicked, this, [&] {ui.textBrowser->clear(); });
}

void QtSubprocessRunTest::startRunPyScript()
{ 
	m_subProcessRunnerWithSpawn.startRun(string(R"(")") + "C:\\Users\\eijpnae\\Documents\\Visual Studio 2015\\Projects\\QtSubprocessRunTest\\x64\\Debug\\SubprocessSpawn.exe" + R"(")" + " " +
		m_subProcessRunnerWithSpawn.getNamePipeName() + " python " +R"(")" + m_pyPath.toStdString() + R"(")");
	//m_subProcessRunner.startRun(std::string("python -u ") +  R"(")" +  m_pyPath.toStdString() + R"(")");
}
QtSubprocessRunTest::~QtSubprocessRunTest()
{
	m_subProcessRunnerWithSpawn.stop();
	//m_subProcessRunner.stop();
}
void QtSubprocessRunTest::stopRunPyScript()
{
	m_subProcessRunnerWithSpawn.stop();
	//m_subProcessRunner.stop();

}

void QtSubprocessRunTest::displayPyStdoutToBorwse(const QString &stdoutcontents)
{
	QString stdoutcontent = std::move(stdoutcontents);
	/*stdoutcontent = "this is test\r\n";*/
	if (stdoutcontent.contains("\r\n\r\n"))
	{
		stdoutcontent = stdoutcontent.left(stdoutcontent.size() - 2);
	}
	this->ui.textBrowser->append(stdoutcontent);
	this->ui.textBrowser->moveCursor(QTextCursor::End);
	this->ui.textBrowser->textCursor().deletePreviousChar();
	this->ui.textBrowser->update();
}
