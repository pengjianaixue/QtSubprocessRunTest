#include "stdafx.h"
#include "CommandShellRunner.h"


CommandShellRunner::CommandShellRunner()
{

}


CommandShellRunner::~CommandShellRunner()
{

}

bool CommandShellRunner::startRunCommand(const string &commandstr)
{
	if ((m_stdoutFileStream = _popen(commandstr.c_str(), "rt")) == nullptr)
		return false;

	while (!feof(m_stdoutFileStream))
	{
		if (fgets(m_psBuffer, 512, m_stdoutFileStream) != nullptr)
		{
			cout << string(m_psBuffer) << std::endl;
		}
	}
	return false;
}

