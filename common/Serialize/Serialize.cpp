#include	"Serialize.hh"

Serialize::Serialize()
{

}

Serialize::~Serialize()
{

}

char		*Serialize::serialize(IEntity *entity)
{
  (void)entity;
  return (NULL);
}

ICommand	*Serialize::unserializeChatInfoCmd(char *cmd)
{
  (void)cmd;
  return (NULL);
}

ICommand	*Serialize::unserializeRoomInfoCmd(char *cmd)
{
  (void)cmd;
  return (NULL);
}

ICommand	*Serialize::unserializeRoomListCmd(char *cmd)
{
  (void)cmd;
  return (NULL);
}

ICommand	*Serialize::unserializeEntityCmd(char *cmd)
{
  (void)cmd;
  return (NULL);
}

ICommand	*Serialize::unserializeInputCmd(char *cmd)
{
  (void)cmd;
  return (NULL);
}

char		*Serialize::serialize(ICommand *cmd)
{
  packet		p;
  std::string	tmp;
  int			i;
  char			*ret;

  ret = new char[65471];
  p.dataType = cmd->getCommandName();
  p.cmdType = cmd->getCommandType();
  tmp = cmd->getCommandArg();
  i = -1;
  while (tmp[++i] != 0)
    p.data[i] = tmp[i];
  p.data[i] = 0;
  p.dataLength = tmp.size() + 8;
  i = -1;
  while (++i != p.dataLength)
    ret[i] = reinterpret_cast<char *>(&p)[i];
  ret[i] = 0;
  return (ret);
}

IEntity		*Serialize::unserializeEntity(char *data)
{
  (void)data;
  return (NULL);
}

#include	<iostream>
ICommand	*Serialize::unserializeCommand(char *data)
{
  packet	p;
  ICommand	*res;

  p = *reinterpret_cast<packet*>(data);
  std::cout << p.data << std::endl;
  switch (p.dataType)
    {
    case CHATINFO:
      break;
	case ROOMINFO:
		break;
	case BASICCMD:
		//res = new BasicCmd();
		//return ();
		break;
	case ROOMLIST:
      break;
    case ENTITY:
      break;
    case INPUTCMD:
      break;
    }
  return (NULL);
}
