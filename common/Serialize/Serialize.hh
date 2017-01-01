#pragma once

#include	<queue>
#include	"IEntity.hpp"
#include	"ICommand.hpp"
#include	"CmdEnum.hh"
#include	"BasicCmd.hh"
#include	"Player.hh"
#include	"PowerUp.hh"
#include	"Barrier.hh"
#include	"ListRoomCmd.hh"
#include	"RoomInfoCmd.hh"
#include	"InputCmd.hh"
#include	"MemTools.hh"
#include	"Missile.hh"
#include	"SuperMissile.hh"
#include	"EndGameCmd.hh"

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
