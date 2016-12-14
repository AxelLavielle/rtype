#pragma once

#include	<string>
#include	"CmdEnum.hh"

class		ICommand
{
public:
  virtual	~ICommand() {}

  virtual CmdType		getCommandType() = 0;
  virtual const std::string	getCommandArg() = 0;
  virtual void			setCommandArg(const std::string &) = 0;
};
