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

int		InputCmd::getId() const
{
	return (_id);
}

void InputCmd::setId(const int id)
{
	_id = id;
	_arg += std::to_string(_id) + _separator;
}

void InputCmd::setCommandArg(const std::string & arg)
{
	std::vector<std::string> vectStr;

	vectStr = split(arg);
	_id = std::stoi(vectStr.at(0));
	_key = vectStr.at(1);
	_arg = arg;
}
