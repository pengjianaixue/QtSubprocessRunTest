// SubprocessSpawn.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../SubProcessRunner/subProcessRunner.h"
#include <string>
#include <thread>
#include <Windows.h>
using std::string;

bool pause();
bool resume();
bool stop();
bool writeNamePipe(const string &processOutput,void* param);

HANDLE hPipe = nullptr;
int main(int argc, char *argv[])
{
	string namePipe = argv[0];
	string runCmd = "";
#ifdef _UNICODE
	
	WCHAR sznamePipe[512] = { 0 };
	::MultiByteToWideChar(CP_ACP, 0, namePipe.c_str(), namePipe.length() + 1, sznamePipe,
		sizeof(sznamePipe) / sizeof(sznamePipe[0]));
	//hPipe  = CreateNamedPipe(sznamePipe, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE , PIPE_UNLIMITED_INSTANCES,4096,4096,0,0);
	if (WaitNamedPipe(sznamePipe, NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		return -1;
	}
	hPipe = CreateFile(sznamePipe, GENERIC_READ | \
		GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hPipe == INVALID_HANDLE_VALUE) 
	{
		return -1;
	}
#else

#endif // _UNICODE
	for (size_t i = 1; i < argc; i++)
	{
		runCmd = runCmd + argv[i] + " ";
	}
	SubProcessRunner processrunner;
	processrunner.startRun(runCmd);
	processrunner.registerReadCallBackFuntion(writeNamePipe);
	processrunner.waitForFinish();
    return 0;
}

bool pause()
{
	return false;
}

bool resume()
{
	return false;
}

bool stop()
{
	return false;
}

bool writeNamePipe(const string &processOutput, void *param)
{
	if(hPipe==nullptr || hPipe == INVALID_HANDLE_VALUE)
		return false;
	DWORD writeNum = 0;
	if (WriteFile(hPipe, processOutput.c_str(), processOutput.length(), &writeNum, NULL) == FALSE)
	{
		return false;
	}
}
