#include	"Serialize.hh"

Serialize::Serialize()
{

}

Serialize::~Serialize()
{

}

char		*Serialize::serialize(IEntity *entity)
{
	packet	p;
	std::string	tmp;
	int		i;
	char		*ret;

	ret = new char[sizeof(packet)];
	MemTools::set(ret, 0, sizeof(packet));
	p.dataType = entity->getType();
	p.cmdType = ENTITY;
	tmp = entity->getArgs();
	std::cout << "tmp = " << tmp << std::endl;
	i = 0;
	while ((unsigned int)i < tmp.size())
	{
		p.data[i] = tmp[i];
		i++;
	}
	p.data[i] = 0;
	p.dataLength = tmp.size() + 7;
	i = -1;
	while (++i != p.dataLength)
		ret[i] = reinterpret_cast<char *>(&p)[i];
	ret[i] = 0;
	return (ret);
}

char		*Serialize::serialize(ICommand *cmd)
{
  packet	p;
  std::string	tmp;
  int		i;
  char		*ret;

  ret = new char[sizeof(packet)];
  MemTools::set(ret, 0, sizeof(packet));
  p.dataType = cmd->getCommandName();
  p.cmdType = cmd->getCommandType();
  tmp = cmd->getCommandArg();
  i = 0;
  while ((unsigned int )i < tmp.size())
  {
	  p.data[i] = tmp[i];
	  i++;
  }
  p.data[i] = 0;
  p.dataLength = tmp.size() + 7;
  i = -1;
  while (++i != p.dataLength)
    ret[i] = reinterpret_cast<char *>(&p)[i];
  ret[i] = 0;
  return (ret);
}

IEntity		*Serialize::unserializeEntity(char *data)
{
  packet	*p;
  Player	*res;
  std::string	tmp;

  tmp = "";
  p = reinterpret_cast<packet*>(data);
  if (p == NULL)
	  return (NULL);
  res = new Player(0, 0);
  res->setType(static_cast<rtype::EntityType>(p->dataType));
  if (!res->setArgs(std::string(p->data)))
  {
	  delete res;
	  return (NULL);
  }
  return (res);
}
#include <iostream>
ICommand	*Serialize::unserializeCommand(char *data)
{
  packet	*p;
  ICommand	*res;

  res = NULL;
  p = reinterpret_cast<packet*>(data);
  switch (p->dataType)
    {
    case CHAT_INFO:
      break;
    case ROOM_INFO:
		res = new RoomInfoCmd();
		break;
    case BASIC_CMD:
      res = new BasicCmd();
      break;
    case ROOM_LIST:
		res = new ListRoomCmd();
		break;
	case INPUT_CMD:
		res = new InputCmd();
		break;
	case ENTITY:
      break;
    default:
      break;
    }
  if (res)
  {
	  //std::cout << "UNSERIALIZE [" << p->data << "]" << std::endl;
	  res->setCommandArg(p->data);
	  res->setCommandType(static_cast<CmdType>(p->cmdType));
  }
  return (res);
}
