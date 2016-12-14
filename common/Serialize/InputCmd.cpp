#include	"InputCmd.hh"

InputCmd::InputCmd()
{

}

InputCmd::~InputCmd()
{

}

CmdName			InputCmd::getCommandName() const
{
  return (INPUTCMD);
}

const std::string	InputCmd::getCommandArg() const
{
	return (_arg);
}

void			InputCmd::setCommandArg(const std::string &arg)
{
	_arg = arg;
}
