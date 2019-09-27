// SubProcessRunner.cpp : 定义控制台应用程序的入口点。
//

#include "subProcessRunner.h"
SubProcessRunner::SubProcessRunner()
{
	m_bThreadQuit = false;
	m_readSubProcessOutputThread = std::make_shared<std::thread>(&SubProcessRunner::readSubProcessOutput, this);
	m_processStatesNotifyThread  = std::make_shared<std::thread>(&SubProcessRunner::_isFinished, this);
}

bool SubProcessRunner::startRun(const string &subprogrammcmd)
{	
	if (m_piProcInfo.hProcess)
	{
		return false;
	}
	if(!initMemberVar())
		return false;
	createStartUpInfo(&m_siStartInfo);
#ifdef UNICODE
	WCHAR szCommmandLine[512] = {0};
	::MultiByteToWideChar(CP_ACP, 0, subprogrammcmd.c_str(), subprogrammcmd.length() + 1, szCommmandLine,
		sizeof(szCommmandLine) / sizeof(szCommmandLine[0]));
#else
	CHAR wszClassName[512] = {0};
	::memcpy_s(wszClassName, subprogrammcmd.length(), subprogrammcmd.c_str(), m_strSubProgrammcmd.length());
#endif // UNICODE
	DWORD dwCreationFlags = (GetConsoleWindow() ? 0 : CREATE_NO_WINDOW);
	dwCreationFlags |= CREATE_UNICODE_ENVIRONMENT;
	if (!::CreateProcess(NULL,
		szCommmandLine, &m_saAttr, &m_saAttr, TRUE,
		dwCreationFlags, NULL, NULL,
		&m_siStartInfo, &m_piProcInfo))
	{
		CloseHandle(m_hReadChildStdOutRead);
		CloseHandle(m_hChildStdInWrite);
		m_hReadChildStdOutRead = NULL;
		m_hChildStdInWrite = NULL;
		QDEBUG(QString("CreateProcess fail ,error code:")+  QString::number(GetLastError()) + "\r\n");
		return false;
	}
	return true;
}

bool SubProcessRunner::isFinished() const
{	
	return m_bThreadQuit;
}
int SubProcessRunner::waitForFinish(unsigned int timeoutMilliseconds)
{
	if (m_piProcInfo.hProcess)
	{
		if (WAIT_OBJECT_0 == ::WaitForSingleObject(m_piProcInfo.hProcess, timeoutMilliseconds))
		{
			DWORD dwExitCode = 0;
			::GetExitCodeProcess(m_piProcInfo.hProcess, &dwExitCode);
			return dwExitCode;
		}
		else
		{
			std::unique_lock<std::mutex> guard(m_threadSwitchmutext, std::try_to_lock);
			if (m_piProcInfo.hThread && m_piProcInfo.hProcess)
			{
				TerminateThread(m_piProcInfo.hThread, -1);
				TerminateProcess(m_piProcInfo.hProcess, -1);
				::CloseHandle(m_piProcInfo.hThread);
				::CloseHandle(m_piProcInfo.hProcess);
				::CloseHandle(m_hReadChildStdOutRead);
				::CloseHandle(m_hChildStdInWrite);
				m_piProcInfo.hThread = nullptr;
				m_piProcInfo.hProcess = nullptr;
				m_hReadChildStdOutRead = nullptr;
				m_hChildStdInWrite = nullptr;
			}

		}
	}
	return -1;
}
bool SubProcessRunner::registerReadCallBackFuntion(READSTDOUTCALLBACKFUN callBackfunction)
{
	if (callBackfunction)
	{
		m_readCallbackfun = callBackfunction;
		return true;
	}
	return false;
}
bool SubProcessRunner::pause()
{
	if (m_piProcInfo.hThread)
	{
		 int ret = ::SuspendThread(m_piProcInfo.hThread);
		 return !ret;
	}
	return false;
}
bool SubProcessRunner::resume()
{
	if (m_piProcInfo.hThread)
	{
		int ret = ::ResumeThread(m_piProcInfo.hThread);
		return !ret;
	}
	return false;
}
bool SubProcessRunner::stop()
{
	std::unique_lock<std::mutex> guard(m_threadSwitchmutext, std::try_to_lock);
	if (m_piProcInfo.hThread && m_piProcInfo.hProcess)
	{
		TerminateThread(m_piProcInfo.hThread,-1);
		TerminateProcess(m_piProcInfo.hProcess, -1);
		::CloseHandle(m_piProcInfo.hThread);
		::CloseHandle(m_piProcInfo.hProcess);
		::CloseHandle(m_hReadChildStdOutRead);
		::CloseHandle(m_hChildStdInWrite);
		m_piProcInfo.hThread = nullptr;
		m_piProcInfo.hProcess = nullptr;
		m_hReadChildStdOutRead = nullptr;
		m_hChildStdInWrite = nullptr;
	}
	return true;
}
//string SubProcessRunner::wirteCmdtoSubprogramm()
//{
//	return string();
//}

SubProcessRunner::~SubProcessRunner()
{
	m_bThreadQuit = true;
	if (m_readSubProcessOutputThread && m_readSubProcessOutputThread->joinable())
	{
		m_readSubProcessOutputThread->join();
		m_readSubProcessOutputThread = nullptr;
	}
	if (m_processStatesNotifyThread && m_processStatesNotifyThread->joinable())
	{
		m_processStatesNotifyThread->join();
		m_processStatesNotifyThread = nullptr;
	}
	stop();
}

void SubProcessRunner::createSecurityAttributes(PSECURITY_ATTRIBUTES pSa)
{
	pSa->bInheritHandle = TRUE;
	pSa->lpSecurityDescriptor = NULL;
	pSa->nLength = sizeof(SECURITY_ATTRIBUTES);
}

bool SubProcessRunner::initMemberVar()
{
	createSecurityAttributes(&m_saAttr);
	if (!::CreatePipe(&m_hReadChildStdOutRead, &m_hChildStdInWrite, &m_saAttr, 0))
		return false;
	return true;
}

void SubProcessRunner::createStartUpInfo(LPSTARTUPINFO lpStartUpInfo)
{
	ZeroMemory(lpStartUpInfo,sizeof(STARTUPINFO));	
	lpStartUpInfo->cb = sizeof(STARTUPINFO);
	lpStartUpInfo->lpReserved = 0;
	lpStartUpInfo->lpDesktop = 0;
	lpStartUpInfo->lpTitle = 0;
	lpStartUpInfo->dwX = (unsigned long)CW_USEDEFAULT;
	lpStartUpInfo->dwY = (unsigned long)CW_USEDEFAULT;
	lpStartUpInfo->dwXSize = (unsigned long)CW_USEDEFAULT;
	lpStartUpInfo->dwYSize = (unsigned long)CW_USEDEFAULT;
	lpStartUpInfo->dwXCountChars = 0;
	lpStartUpInfo->dwYCountChars = 0;
	lpStartUpInfo->dwFillAttribute = 0;
	lpStartUpInfo->dwFlags =	 STARTF_USESTDHANDLES;
	lpStartUpInfo->wShowWindow = SW_SHOWNORMAL;
	lpStartUpInfo->cbReserved2 = 0;
	lpStartUpInfo->lpReserved2 = 0;
	lpStartUpInfo->hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	lpStartUpInfo->hStdOutput = m_hChildStdInWrite;
	lpStartUpInfo->hStdError = m_hChildStdInWrite; 

}

void SubProcessRunner::readSubProcessOutput()
{

	char out_buffer[10000] = {0};
	while (!m_bThreadQuit)
	{
		if (m_piProcInfo.hProcess && m_hReadChildStdOutRead)
		{
			DWORD dwRead = 0;
			DWORD dwAvial = 0;
			DWORD dwLefe = 0;
			std::unique_lock<std::mutex> guard(m_threadSwitchmutext, std::try_to_lock);
			BOOL bSuccess = ::ReadFile(m_hReadChildStdOutRead, out_buffer, sizeof(out_buffer), &dwRead, nullptr);
			if (bSuccess && dwRead > 0)
			{
				if (m_readCallbackfun)
				{
					m_readCallbackfun(string(out_buffer), this);
				}
				#ifdef QT_DLL
						emit signal_SendSubProcessStdoutContents(QString(out_buffer));
				#endif
				QDEBUG(QString("Subprocess output:") + out_buffer + "\r\n")
				ZeroMemory(out_buffer, sizeof(out_buffer));
			}
			else
			{
				string errorcode = std::to_string(GetLastError()).c_str();
				QDEBUG(QString("Read Pipe fail ,the error code :") + std::to_string(GetLastError()).c_str() + "\r\n")
			}
		}
		std::this_thread::yield();
	}
	m_bTerminateFlag = true;
	return;
}

void SubProcessRunner::_isFinished()
{
	while (!m_bTerminateFlag)
	{
		if (m_piProcInfo.hProcess)
		{
			DWORD res =  ::WaitForSingleObject(m_piProcInfo.hThread, 0);
			if (res == WAIT_OBJECT_0)
			{
				if(CancelSynchronousIo(m_readSubProcessOutputThread->native_handle()))
				{
					std::unique_lock<std::mutex> guard(m_threadSwitchmutext, std::try_to_lock);
					::CloseHandle(m_piProcInfo.hThread);
					::CloseHandle(m_piProcInfo.hProcess);
					::CloseHandle(m_hReadChildStdOutRead);
					::CloseHandle(m_hChildStdInWrite);
					m_piProcInfo.hThread = nullptr;
					m_piProcInfo.hProcess = nullptr;
					m_hReadChildStdOutRead = nullptr;
					m_hChildStdInWrite = nullptr;
				}
				else 
				{
					QDEBUG(QString("CancelSynchronousIo Error code:" + QString::number(GetLastError())));
					std::this_thread::yield();
				}
			}
		}
		else if (!m_bTerminateFlag)
		{
			CancelSynchronousIo(m_readSubProcessOutputThread->native_handle());
		}
		std::this_thread::yield();
		
	}
	
}
