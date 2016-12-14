#pragma once

#include	"ACommand.hh"

class		ListInfoCmd : public ACommand
{
public:
  ListInfoCmd();
  virtual	~ListInfoCmd();

  virtual CmdName		getCommandName() const;
  virtual const std::string	getCommandArg() const;
  virtual void			setCommandArg(const std::string &);

protected:
  std::string	arg;
};
