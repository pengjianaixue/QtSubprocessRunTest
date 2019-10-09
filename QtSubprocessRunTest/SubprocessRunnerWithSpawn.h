#pragma once

#include <QObject>
#include <string>
#include <functional>
#include <memory>
#include <thread>
#include <Windows.h>
using std::string;
class SubprocessRunnerWithSpawn : public QObject
{
	Q_OBJECT
public:
	using READSTDOUTCALLBACKFUN = std::function<bool(const string&, void *)>;
	SubprocessRunnerWithSpawn(QObject *parent = nullptr);
	~SubprocessRunnerWithSpawn();
	bool startRun(const string &subprogrammcmd  = "./SubprocessSpawn.exe ");
	bool isFinished()const;
	string getNamePipeName() const;
	int  waitForFinish(unsigned int timeoutMilliseconds = 180 * 1000);
	//bool registerReadCallBackFuntion(READSTDOUTCALLBACKFUN callBackfunction);
	bool pause();
	bool resume();
	bool stop();
signals:
	void sigals_sendSubProcessOutput(const QString &msg);
private:
	bool createNamedPipe();
	void createStartUpInfo(LPSTARTUPINFO lpStartUpInfo);
	void readSubProcessOutput();
	bool wirteToSubProcess(const string &wirtemsg);
	static void LPOVERLAPPED_COMPLETION_ROUTINE(
		_In_    DWORD dwErrorCode,
		_In_    DWORD dwNumberOfBytesTransfered,
		_Inout_ LPOVERLAPPED lpOverlapped
	);
	static  void CALLBACK waitCallBack(
		_Inout_     PTP_CALLBACK_INSTANCE Instance,
		_Inout_opt_ PVOID                 Context,
		_Inout_     PTP_WAIT              Wait,
		_In_        TP_WAIT_RESULT        WaitResult);
private:
	HANDLE							m_namePipeHandle				= { nullptr };
	PROCESS_INFORMATION				m_piProcInfo					= { nullptr };
	STARTUPINFO						m_siStartInfo					= {};
	std::shared_ptr<std::thread>	m_readSubProcessOutputThread	= { nullptr };
	volatile bool					m_readthreadflag				= { true };
	volatile bool					m_subprocessrunflag				= { false };
	string							m_strNamePipe					= { "\\\\.\\pipe\\namedpipe_subprocess" };
	PTP_WAIT						m_subprocessThreadpoolWaitObj	= { nullptr };
	HANDLE							m_hPipeReadFile					= { nullptr };
};

struct NamePipeoverlapped:OVERLAPPED
{
	SubprocessRunnerWithSpawn *m_classpointer;
	NamePipeoverlapped(SubprocessRunnerWithSpawn *classpointer = nullptr)
		:m_classpointer(classpointer), OVERLAPPED({0})
	{};

};
