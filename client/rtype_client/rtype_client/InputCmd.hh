#pragma once

#include	"ACommand.hh"

class		InputCmd : public ACommand
{
public:
  InputCmd();
  virtual	~InputCmd();

  virtual CmdName		getCommandName() const;
  virtual const std::string	getCommandArg() const;
  virtual void			setCommandArg(const std::string &);

protected:
  std::string	arg;
};
