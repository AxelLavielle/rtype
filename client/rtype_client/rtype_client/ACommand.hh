#pragma once

#include	<string>
#include	"ICommand.hpp"

class		ACommand : public ICommand
{
public:
  ACommand();
  virtual	~ACommand();

  virtual CmdName		getCommandName() = 0;
  virtual const std::string	getCommandArg() = 0;
  virtual void			setCommandArg(const std::string &) = 0;

protected:
  CmdType	cmdType;
  std::string	arg;
};
