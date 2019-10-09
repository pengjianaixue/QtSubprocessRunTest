// SubprocessSpawn.cpp 
//

#include "stdafx.h"
#include "../SubProcessRunner/subProcessRunner.h"
#include <string>
#include <thread>
#include <functional>
#include <Windows.h>
#include <map>
#include <iostream>
using std::string;


using ProcessOperationFun = std::function<bool()>;
bool pause();
bool resume();
bool stop();
bool writeNamePipe(const string &processOutput,void* param);
bool readNamePipe();
std::map<std::string, ProcessOperationFun> operationdict;
HANDLE hPipe = nullptr;
SubProcessRunner *processrunner = nullptr;
volatile bool readflag = true;
int main(int argc, char *argv[])
{
	std::cout << "command line param counter:" << argc << std::endl;
	if (argc<2)
	{
		system("pause");
		return -1;
	}
	string namePipe = argv[1];
	string runCmd = "";
#ifdef _UNICODE
	WCHAR sznamePipe[512] = { 0 };
	::MultiByteToWideChar(CP_ACP, 0, namePipe.c_str(), namePipe.length() + 1, sznamePipe,
		sizeof(sznamePipe) / sizeof(sznamePipe[0]));
#else
	CHAR sznamePipe[512] = { 0 };
	memcpy_s(sznamePipe, namePipe.length(), namePipe.c_str(), namePipe.length());
#endif // _UNICODE
	if (WaitNamedPipe(sznamePipe, NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		std::cout << "WaitNamedPipe failed,error code is:" << GetLastError() << std::endl;
		system("pause");
		return -1;
	}
	hPipe = CreateFile(sznamePipe, GENERIC_READ | \
		GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "CreateFile failed,error code is:" << GetLastError() << std::endl;
		system("pause");
		return -1;
	}
	for (size_t i = 2; i < argc; i++)
	{
		runCmd = runCmd + argv[i] + " ";

	}
	std::cout << "runCmd is:" << runCmd << std::endl;
	operationdict.insert({"pause",pause});
	operationdict.insert({ "stop",stop });
	operationdict.insert({ "resume",resume });
	std::thread readPipeNameThread(readNamePipe);
	processrunner  = new SubProcessRunner;
	if (processrunner->startRun(R"("C:\Users\eijpnae\Documents\Visual Studio 2015\Projects\QtSubprocessRunTest\x64\Debug\test.exe")"))
	{
		std::cout << "startRun ...." << std::endl;
		if (!processrunner->registerReadCallBackFuntion(writeNamePipe))
		{
			std::cout << "register CallBackFuntion failed ...." << std::endl;
		}
		processrunner->waitForFinish();
	}
	else
	{
		std::cout << "startRun failed,error code  is:" << GetLastError() << std::endl;
	}
	readflag = false;
	CancelSynchronousIo(readPipeNameThread.native_handle());
	readPipeNameThread.join();
	system("pause");
    return 0;
	
}

bool pause()
{
	if (processrunner)
	{
		processrunner->pause();
		return true;
	}
	return false;
}

bool resume()
{
	if (processrunner)
	{
		processrunner->resume();
		return true;
	}
	return false;
}

bool stop()
{
	if (processrunner)
	{
		processrunner->stop();
		return true;
	}
	return false;
}

bool writeNamePipe(const string &processOutput, void *param)
{
	if(hPipe == nullptr || hPipe == INVALID_HANDLE_VALUE)
		std::cout << "hPipe is unuseable " << std::endl;
		return false;
	DWORD writeNum = 0;
	std::cout << "subprocessOutput is:" << processOutput << std::endl;
	if (WriteFile(hPipe, processOutput.c_str(), processOutput.length(), &writeNum, NULL) == FALSE)
	{
		std::cout << "WriteFile failed, error code  is:" << GetLastError() << std::endl;
		return false;
	}
}

bool readNamePipe()
{
	while (readflag)
	{
		if (hPipe == nullptr || hPipe == INVALID_HANDLE_VALUE)
			return false;
		DWORD readNum = 0;
		char readBuff[512] = { 0 };
		if (ReadFile(hPipe, readBuff, sizeof(readBuff), &readNum, NULL) == FALSE)
		{
			return false;
		}
		if (readNum>0)
		{
			operationdict[readBuff]();
			return true;
		}
		return false;
	}
	return true;
}
