#pragma once

#include	"IEntity.hpp"
#include	"ICommand.hpp"
#include	"CmdEnum.hh"
#include	"BasicCmd.hh"
#include	"Player.hh"
#include	"PowerUp.hh"
#include	"Monster.hh"
#include	"Barrier.hh"
#include	"ListRoomCmd.hh"
#include	"RoomInfoCmd.hh"
#include	"InputCmd.hh"

class		Serialize
{
public:
  Serialize();
  static char		*serialize(IEntity *);
  static char		*serialize(ICommand *);
  static IEntity	*unserializeEntity(char *);
  static ICommand	*unserializeCommand(char *);
  ~Serialize();

private:
  struct	packet
  {
	short	dataLength;
	short	dataType;
    short	cmdType;
    char	data[65465];
  };
};
