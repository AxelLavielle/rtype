#include	"ChatInfoCmd.hh"

ChatInfoCmd::ChatInfoCmd()
{

}

ChatInfoCmd::~ChatInfoCmd()
{

}

CmdName			ChatInfoCmd::getCommandName() const
{
  return (CHAT_INFO);
}

const std::string	ChatInfoCmd::getCommandArg() const
{
	return (_arg);
}

void			ChatInfoCmd::setCommandArg(const std::string &arg)
{
	_arg = arg;
}
