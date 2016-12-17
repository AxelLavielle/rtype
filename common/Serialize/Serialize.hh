#pragma once

#include	"IEntity.hpp"
#include	"ICommand.hpp"
#include	"CmdEnum.hh"
#include	"BasicCmd.hh"

class		Serialize
{
public:
  Serialize();
  char		*serialize(IEntity *);
  char		*serialize(ICommand *);
  IEntity	*unserializeEntity(char *);
  ICommand	*unserializeCommand(char *);
  ~Serialize();

private:
  ICommand	*unserializeChatInfoCmd(char*);
  ICommand	*unserializeRoomInfoCmd(char*);
  ICommand	*unserializeRoomListCmd(char*);
  ICommand	*unserializeEntityCmd(char*);
  ICommand	*unserializeInputCmd(char*);

  struct	packet
  {
    short	dataType;
	short	cmdType;
    short	dataLength;
    char	data[65467];
  };
};
