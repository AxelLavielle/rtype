#pragma once

#include	"ACommand.hh"

class		EntityCmd : public ACommand
{
public:
  EntityCmd();
  virtual	~EntityCmd();

  virtual CmdName		getCommandName() const;
  virtual const std::string	getCommandArg() const;
  virtual void			setCommandArg(const std::string &);

protected:
  std::string	_arg;
};
