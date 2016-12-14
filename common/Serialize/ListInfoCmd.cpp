#include	"ListInfoCmd.hh"

ListInfoCmd::ListInfoCmd()
{

}

ListInfoCmd::~ListInfoCmd()
{

}

CmdName			ListInfoCmd::getCommandName() const
{
  return (ROOMLIST);
}

const std::string	ListInfoCmd::getCommandArg() const
{
  
}

void			ListInfoCmd::setCommandArg(const std::string &)
{
  
}
