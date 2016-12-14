#pragma once

#include	"ACommand.hh"

class		RoomInfoCmd : public ACommand
{
public:
  RoomInfoCmd();
  virtual	~RoomInfoCmd();

  virtual CmdName		getCommandName() const;
  virtual const std::string	getCommandArg() const;
  virtual void			setCommandArg(const std::string &);

protected:
  std::string	arg;
};
