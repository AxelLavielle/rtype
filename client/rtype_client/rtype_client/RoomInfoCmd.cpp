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

}

void			RoomInfoCmd::setCommandArg(const std::string &)
{

}
