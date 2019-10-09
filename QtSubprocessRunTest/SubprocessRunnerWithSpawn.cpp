#include "SubprocessRunnerWithSpawn.h"

SubprocessRunnerWithSpawn::SubprocessRunnerWithSpawn(QObject *parent)
	: QObject(parent)
{
	m_readSubProcessOutputThread = std::make_shared<std::thread>(&SubprocessRunnerWithSpawn::readSubProcessOutput, this);
	m_subprocessThreadpoolWaitObj = ::CreateThreadpoolWait(waitCallBack, this, nullptr);
}

SubprocessRunnerWithSpawn::~SubprocessRunnerWithSpawn()
{
	m_readthreadflag = false;
	if (m_readSubProcessOutputThread->joinable())
	{
		m_readSubProcessOutputThread->join();
	}
}

bool SubprocessRunnerWithSpawn::startRun(const string &subprogrammcmd)
{
	int errorcode = 0;
	if (createNamedPipe())
	{
#ifdef UNICODE
		WCHAR szCommmandLine[512] = { 0 };
		::MultiByteToWideChar(CP_ACP, 0, subprogrammcmd.c_str(), subprogrammcmd.length() + 1, szCommmandLine,
			sizeof(szCommmandLine) / sizeof(szCommmandLine[0]));
#else
		CHAR wszClassName[512] = { 0 };
		::memcpy_s(wszClassName, subprogrammcmd.length(), subprogrammcmd.c_str(), m_strSubProgrammcmd.length());
#endif // UNICODE 
		createStartUpInfo(&m_siStartInfo);
		if (CreateProcess(nullptr, szCommmandLine, nullptr, nullptr, false,CREATE_NEW_CONSOLE,  nullptr, nullptr, &m_siStartInfo, &m_piProcInfo))
		{
			::SetThreadpoolWait(m_subprocessThreadpoolWaitObj, m_piProcInfo.hProcess,0);
			m_subprocessrunflag = true;
		}
		else
		{
			errorcode = GetLastError();

		}
	}
	return false;
}

bool SubprocessRunnerWithSpawn::isFinished() const
{
	return m_subprocessrunflag;
}

string SubprocessRunnerWithSpawn::getNamePipeName() const
{
	return m_strNamePipe;
}

int SubprocessRunnerWithSpawn::waitForFinish(unsigned int timeoutMilliseconds)
{
	::WaitForSingleObject(m_piProcInfo.hProcess, timeoutMilliseconds);
	m_subprocessrunflag = false;
	return 0;
}

//bool SubprocessRunnerWithSpawn::registerReadCallBackFuntion(READSTDOUTCALLBACKFUN callBackfunction)
//{
//
//	return false;
//}

bool SubprocessRunnerWithSpawn::pause()
{
	
	return wirteToSubProcess("pause");
}

bool SubprocessRunnerWithSpawn::resume()
{
	
	return wirteToSubProcess("resume");
}

bool SubprocessRunnerWithSpawn::stop()
{
	
	return wirteToSubProcess("stop");
}

bool SubprocessRunnerWithSpawn::createNamedPipe()
{

	
#ifdef _UNICODE
	WCHAR sznamePipe[512] = { 0 };
	::MultiByteToWideChar(CP_ACP, 0, m_strNamePipe.c_str(), m_strNamePipe.length() + 1, sznamePipe,
		sizeof(sznamePipe) / sizeof(sznamePipe[0]));
	/*hPipe = CreateFile(sznamePipe, GENERIC_READ | \
		GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		return -1;
	}*/
#else
	CHAR sznamePipe[512] = { 0 };
	memcpy_s(sznamePipe, m_strNamePipe.length(), m_strNamePipe.c_str(), m_strNamePipe.length());
#endif
	m_namePipeHandle = CreateNamedPipe(sznamePipe, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, PIPE_UNLIMITED_INSTANCES, 4096, 4096, 0, 0);
	if (!m_namePipeHandle || m_namePipeHandle == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	m_hPipeReadFile = CreateFile(sznamePipe, GENERIC_READ | \
		GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hPipeReadFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}

void SubprocessRunnerWithSpawn::createStartUpInfo(LPSTARTUPINFO lpStartUpInfo)
{
	ZeroMemory(lpStartUpInfo, sizeof(STARTUPINFO));
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
	lpStartUpInfo->dwFlags = STARTF_USESHOWWINDOW;
	lpStartUpInfo->wShowWindow = SW_SHOWNORMAL;
	lpStartUpInfo->cbReserved2 = 0;

}

void SubprocessRunnerWithSpawn::readSubProcessOutput()
{
	while (m_readthreadflag)
	{
		if (m_subprocessrunflag)
		{
			char readBuff[4096] = { 0 };
			if (::ConnectNamedPipe(m_namePipeHandle, NULL))
			{
				DWORD dwReadSize = 0;
				/*NamePipeoverlapped overlappedstruct(this);
				BOOL bRet = ::ReadFileEx(m_namePipeHandle, readBuff, 1024, &overlappedstruct, &dwWriteSize, NULL);*/
				BOOL bRet = ::ReadFile(m_hPipeReadFile, readBuff, 1024, &dwReadSize, NULL);
				if (bRet && dwReadSize > 0)
				{
					emit sigals_sendSubProcessOutput(readBuff);
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	

}

bool SubprocessRunnerWithSpawn::wirteToSubProcess(const string &wirtemsg)
{
	if (!m_subprocessrunflag)
	{
		return false;
	}
	if (::ConnectNamedPipe(m_namePipeHandle, NULL))
	{
		DWORD dwWriteSize = 0;
		BOOL bRet = ::WriteFile(m_hPipeReadFile, wirtemsg.c_str(), wirtemsg.length(), &dwWriteSize, NULL);
		if (bRet && dwWriteSize > 0)
		{
			return  true;
		}
		return false;
	}
	return false;
}

void SubprocessRunnerWithSpawn::LPOVERLAPPED_COMPLETION_ROUTINE(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
{

	/*NamePipeoverlapped *Overlapped = (NamePipeoverlapped*)lpOverlapped;
	emit Overlapped->m_classpointer->sigals_sendSubProcessOutput(readBuff);*/

}

void SubprocessRunnerWithSpawn::waitCallBack(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PTP_WAIT Wait, TP_WAIT_RESULT WaitResult)
{
	SubprocessRunnerWithSpawn *classinstance = static_cast<SubprocessRunnerWithSpawn *>(Context);
	if (WaitResult == WAIT_OBJECT_0)
	{
		classinstance->m_subprocessrunflag = false;
		CancelSynchronousIo(classinstance->m_readSubProcessOutputThread->native_handle());
	}
}
