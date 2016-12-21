#include "BasicCmd.hh"



BasicCmd::BasicCmd()
{
	_cmdName = BASIC_CMD;
}


BasicCmd::~BasicCmd()
{
}

void BasicCmd::addArg(const std::string & str)
{
	_argList.push_back(str);
	_arg += str + _separator;
}

void BasicCmd::setCommandArg(const std::string & arg)
{
	_arg = arg;
	_argList = split(arg);
}

std::string BasicCmd::getArg(const int index) const
{
	if (index >= _argList.size())
		return ("");
	return (_argList[index]);
}

std::vector<std::string> BasicCmd::getAllArg() const
{
	return (_argList);
}
