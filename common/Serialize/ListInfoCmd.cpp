#include	"ListInfoCmd.hh"

ListInfoCmd::ListInfoCmd()
{

}

ListInfoCmd::~ListInfoCmd()
{

}

CmdName			ListInfoCmd::getCommandName() const
{
  return (ROOM_LIST);
}

const std::string	ListInfoCmd::getCommandArg() const
{
	return (_arg);
}

void			ListInfoCmd::setCommandArg(const std::string &arg)
{
	_arg = arg;
}
