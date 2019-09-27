#pragma once
#include <string>
#include <Windows.h>
#include <process.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <functional>
#include <thread>
#include <memory>
#include <mutex>
#include <iostream>
#include <atomic>
#ifdef QT_DLL
	#include <QObject>
	#include <QDebug>
#endif


#ifdef _DEBUG 
	#ifdef QT_DLL
		#define	QDEBUG(TRACE)	qDebug() << TRACE;
	#else
		#define	QDEBUG(TRACE)	
	#endif // QT_DLL
#else
	#define	QDEBUG(TRACE)
#endif // DEBUG


using std::string;
#ifdef QT_DLL
	class SubProcessRunner :public QObject
	{
		Q_OBJECT
#else
	class SubProcessRunner
	{
#endif // QT_DLL
public:
	using READSTDOUTCALLBACKFUN = std::function<bool(const string&,void *)>;
	SubProcessRunner();
	//API 
	bool startRun(const string &subprogrammcmd);
	bool isFinished()const;
	int  waitForFinish(unsigned int timeoutMilliseconds = 180*1000);
	bool registerReadCallBackFuntion(READSTDOUTCALLBACKFUN callBackfunction);
	bool pause();
	bool resume();
	bool stop();
	//string wirteCmdtoSubprogramm();
	virtual ~SubProcessRunner();
#ifdef QT_DLL
	signals :
			void signal_SendSubProcessStdoutContents(const QString& StdoutContents);
#endif
private:
	void createSecurityAttributes(PSECURITY_ATTRIBUTES pSa);
	bool initMemberVar();
	void createStartUpInfo(LPSTARTUPINFO lpStartUpInfo);
	void readSubProcessOutput();
	void _isFinished();
private:
	string	m_strSubProgrammcmd;
	volatile bool    m_bThreadQuit									= {true};
	HANDLE  m_hReadChildStdOutRead									= { nullptr };			
	HANDLE  m_hChildStdInWrite										= { nullptr };			
	HANDLE  m_hStdErrWrite											= { nullptr };		
	SECURITY_DESCRIPTOR  m_sd										= {};
	STARTUPINFO m_siStartInfo										= {};					
	SECURITY_ATTRIBUTES				m_saAttr						= {};
	PROCESS_INFORMATION				m_piProcInfo					= { nullptr };
	READSTDOUTCALLBACKFUN			m_readCallbackfun				= {nullptr};
	std::shared_ptr<std::thread>	m_readSubProcessOutputThread	= { nullptr };
	std::shared_ptr<std::thread>	m_processStatesNotifyThread		= { nullptr };
	std::mutex						m_mutex							= {};
	LPOVERLAPPED_COMPLETION_ROUTINE	m_readPipeOverlappedCallbackfun	= {nullptr};
	char							m_readPipeBufffer[64]			= {};
	HWND						    m_consoleWindowHanlde			= { nullptr };
	FILE*							m_consolestdoutstream			= { nullptr };
	HANDLE							m_threadTriggerEventHandle		= { ::CreateEvent(nullptr,FALSE,FALSE,TEXT(""))};
	std::mutex						m_threadSwitchmutext			= {};
	volatile bool					m_bTerminateFlag				= { false };
};	

class Mutex_guard 
{
public:
	explicit Mutex_guard(std::mutex &mutex) :m_guardmutex(mutex) { m_guardmutex.lock(); };
	~Mutex_guard() { m_guardmutex.unlock(); };
private:
	std::mutex &m_guardmutex;

};

