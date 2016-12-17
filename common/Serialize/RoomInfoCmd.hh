#pragma once

#include	"ACommand.hh"

struct		RoomInfoCmd : public ACommand
{
public:
  RoomInfoCmd();
  virtual	~RoomInfoCmd();

protected:
  std::string	_arg;
};
