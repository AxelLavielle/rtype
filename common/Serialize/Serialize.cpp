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
  std::string	tmps;
  int		i;
  char		*ret;
  int		j;
  double	tmpd;
  int		tmpi;

  ret = new char[sizeof(packet)];
  MemTools::set(ret, 0, sizeof(packet));
  p.dataType = entity->getType();
  p.cmdType = ENTITY;
  j = 0;
  tmpd = entity->getPosX();
  i = -1;
  while (++i != 8)
    p.data[j++] = reinterpret_cast<char*>(&(tmpd))[i];

  tmpd = entity->getPosY();
  i = -1;
  while (++i != 8)
    p.data[j++] = reinterpret_cast<char*>(&(tmpd))[i];

  tmpd = entity->getSpeedX();
  i = -1;
  while (++i != 8)
    p.data[j++] = reinterpret_cast<char*>(&(tmpd))[i];

  tmpd = entity->getSpeedY();
  i = -1;
  while (++i != 8)
    p.data[j++] = reinterpret_cast<char*>(&(tmpd))[i];

  tmpi = entity->getLife();
  i = -1;
  while (++i != 4)
	  p.data[j++] = reinterpret_cast<char*>(&(tmpi))[i];

  tmpd = entity->getHeight();
  i = -1;
  while (++i != 8)
	  p.data[j++] = reinterpret_cast<char*>(&(tmpd))[i];

  tmpd = entity->getWidth();
  i = -1;
  while (++i != 8)
	  p.data[j++] = reinterpret_cast<char*>(&(tmpd))[i];

  tmps = entity->getSpriteRepo();
  i = -1;
  while (tmps[++i] != 0)
    p.data[j++] = tmps[i];
  p.data[j++] = ',';

  tmps = entity->getName();
  i = -1;
  while (tmps[++i] != 0)
    p.data[j++] = tmps[i];
  p.dataLength = j + 6;
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
  while (i < tmp.size())
  {
	  p.data[i] = tmp[i];
	  i++;
  }
  //p.data[i] = 0;
  p.dataLength = tmp.size() + 6;
  i = -1;
  while (++i != p.dataLength)
    ret[i] = reinterpret_cast<char *>(&p)[i];
  ret[i] = 0;
  i = 0;
  return (ret);
}

IEntity		*Serialize::unserializeEntity(char *data)
{
  packet	*p;
  IEntity	*res;
  int		i;
  std::string	tmp;

  tmp = "";
  p = reinterpret_cast<packet*>(data);
  if (p == NULL)
	  return (NULL);
  switch (static_cast<rtype::EntityType>(p->dataType))
    {
    case rtype::EntityType::PLAYER:
      res = new Player();
      break;
    case rtype::EntityType::POWER_UP:
      res = new PowerUp();
      break;
    case rtype::EntityType::MONSTER:
      res = new Monster();
      break;
    case rtype::EntityType::BARRIER:
      res = new Barrier();
      break;
    default:
      res = NULL;
      break;
    }
  if (res == NULL)
    return (NULL);
  res->setType(static_cast<rtype::EntityType>(p->dataType));
  res->setPosX(*reinterpret_cast<double *>(&p->data[0]));
  res->setPosY(*reinterpret_cast<double *>(&p->data[8]));
  res->setSpeedX(*reinterpret_cast<double *>(&p->data[16]));
  res->setSpeedY(*reinterpret_cast<double *>(&p->data[24]));
  res->setLife(*reinterpret_cast<int *>(&p->data[32]));
  res->setHeight(*reinterpret_cast<double *>(&p->data[36]));
  res->setWidth(*reinterpret_cast<double *>(&p->data[44]));
  i = 58;
  while (data[i] != ',')
  {
	  tmp += data[i];
	  i++;
  }
  res->setSpriteRepo(tmp);
  res->setName(std::string(&data[i + 1]));
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
