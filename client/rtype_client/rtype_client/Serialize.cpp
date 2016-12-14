#include	"Serialize.hh"

Serialize::Serialize()
{

}

Serialize::~Serialize()
{

}

char		*Serialize::serialize(IEntity *entity)
{
  return (NULL);
}

char		*Serialize::serializeChatInfo(ICommand *cmd)
{
  return (NULL);
}

char		*Serialize::serializeRoomInfo(ICommand *cmd)
{
  return (NULL);
}

char		*Serialize::serializeRoomList(ICommand *cmd)
{
  return (NULL);
}

char		*Serialize::serializeEntity(ICommand *cmd)
{
  return (NULL);
}

char		*Serialize::serializeInput(ICommand *cmd)
{
  return (NULL);
}

ICommand	*Serialize::unserializeChatInfo(ICommand *cmd)
{
  return (NULL);
}

ICommand	*Serialize::unserializeRoomInfo(ICommand *cmd)
{
  return (NULL);
}

ICommand	*Serialize::unserializeRoomList(ICommand *cmd)
{
  return (NULL);x
}

ICommand	*Serialize::unserializeEntity(ICommand *cmd)
{
  return (NULL);
}

ICommand	*Serialize::unserializeInput(ICommand *cmd)
{
  return (NULL);
}

char		*Serialize::serialize(ICommand *cmd)
{
  CmdName	cmdName;

  cmdName = cmd->getCommandType();
  switch (cmdName)
    {
    case CHATINFO:
      newCmd = serializeChatInfo(cmd);
      break;
    case ROOMINFO:
      newCmd = serializeRoomInfo(cmd);
      break;
    case ROOMLIST:
      newCmd = serializeRoomList(cmd);
      break;
    case ENTITY:
      newCmd = serializeEntity(cmd);
      break;
    case INPUT:
      newCmd = serializeInput(cmd);
      break;
    case default:
      newCmd = NULL;
      break;
    }
  return (newCmd);
}

IEntity		Serialise::unserializeEntity(char *data)
{

}

ICommand	Serialise::unserializeCommand(char *data)
{

}
