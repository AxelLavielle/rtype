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
	_arg += _separator + str;
}

std::vector<std::string> BasicCmd::split(const std::string &s)
{
	std::vector<std::string> elems;
	std::stringstream		ss;

	ss.str(s);
	std::string item;

	while (std::getline(ss, item, _separator))
	{
		elems.push_back(item);
	}
	return (elems);
}

void BasicCmd::setCommandArg(const std::string & arg)
{
	_arg = arg;
	_argList = split(arg);
}

std::string BasicCmd::getArg(const int index) const
{
	return (_argList[index]);
}

std::vector<std::string> BasicCmd::getAllArg() const
{
	return (_argList);
}
