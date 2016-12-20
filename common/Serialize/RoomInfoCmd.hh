#pragma once

#include	"ACommand.hh"

struct		RoomInfoCmd : public ACommand
{
public:
  RoomInfoCmd();
  virtual	~RoomInfoCmd();

private:
  std::string	_arg;
};
