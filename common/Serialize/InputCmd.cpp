#include	"InputCmd.hh"

InputCmd::InputCmd()
{

}

InputCmd::~InputCmd()
{

}

CmdName			InputCmd::getCommandName() const
{
  return (INPUT_CMD);
}

std::string InputCmd::getKey() const
{
	return (_key);
}

void InputCmd::setKey(const std::string & key)
{
	_key = key;
	_arg += _key;
}

void InputCmd::setCommandArg(const std::string & arg)
{
	_key = arg;
	_arg = arg;
}
