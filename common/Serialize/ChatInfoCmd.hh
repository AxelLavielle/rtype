#pragma once

#include	"ACommand.hh"

class		ChatInfoCmd : public ACommand
{
public:
  ChatInfoCmd();
  virtual	~ChatInfoCmd();

  virtual CmdName		getCommandName() const;
  virtual const std::string	getCommandArg() const;
  virtual void			setCommandArg(const std::string &);

private:
  std::string	_arg;
};
