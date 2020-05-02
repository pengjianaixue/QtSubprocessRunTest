#include "stdafx.h"
#include "subProcessRunner.h"
#include "CommandShellRunner.h"
#include <iostream>
bool readSubPorcessOutputCallBack(const std::string &outputinfor,void* externparam)
{
	std::cout << outputinfor << std::endl;
	return true;
}
int main()
{
	{
		AllocConsole();
		SubProcessRunner test;
		test.startRun("python -u ./test.py");
		Sleep(3000);
		bool re = test.pause();
		Sleep(3000);
		bool ret = test.resume();
		test.waitForFinish();
		/*SubProcessRunner test;
		test.registerReadCallBackFuntion(readSubPorcessOutputCallBack);
		test.startRun("python -u ./test.py");
		Sleep(1000);
		test.pause();
		Sleep(1000);
		test.resume();
		test.waitForFinish();*/
		
	}
	_CrtDumpMemoryLeaks();
	system("pause");


}