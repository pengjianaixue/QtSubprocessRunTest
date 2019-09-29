#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <thread>
using std::cout;
using std::string;
class CommandShellRunner
{
public:
	CommandShellRunner();
	~CommandShellRunner();
public:
	bool startRunCommand(const string &commandstr);
private:
	std::shared_ptr<std::thread>	m_readStdoutThread =  { nullptr };
	FILE							*m_stdoutFileStream = { nullptr };
	//std::shared_ptr<char>			m_psBuffer = std::make_shared<char>(new char[10000], std::default_delete<char[]>());
	char m_psBuffer[10000]			= { 0 };

};

