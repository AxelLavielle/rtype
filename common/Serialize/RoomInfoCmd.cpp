#include	"RoomInfoCmd.hh"

RoomInfoCmd::RoomInfoCmd()
{

}

RoomInfoCmd::~RoomInfoCmd()
{

}

CmdName			RoomInfoCmd::getCommandName() const
{
  return (ROOMINFO);
}

const std::string	RoomInfoCmd::getCommandArg() const
{
	return (_arg);
}

void			RoomInfoCmd::setCommandArg(const std::string &arg)
{
	_arg = arg;
}
