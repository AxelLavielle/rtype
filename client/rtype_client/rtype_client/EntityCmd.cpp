#include	"EntityCmd.hh"

EntityCmd::EntityCmd()
{

}

EntityCmd::~EntityCmd()
{

}

CmdName			EntityCmd::getCommandName() const
{
  return (ENTITY);
}

const std::string	EntityCmd::getCommandArg() const
{

}

void			EntityCmd::setCommandArg(const std::string &)
{

}
