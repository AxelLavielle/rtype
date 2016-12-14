#pragma once

#include	<string>
#include	"CmdEnum.hh"

class		ICommand
{
public:
  virtual	~ICommand() {}

  virtual CmdName		getCommandName() const = 0;
  virtual const std::string	getCommandArg() const = 0;
  virtual void			setCommandArg(const std::string &) = 0;
};
