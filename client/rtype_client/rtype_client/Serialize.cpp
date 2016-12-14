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
  packet	*p;
  std::string	tmp;
  int		i;
  char		*ret;

  ret = new char[65471];
  p = new packet[1];
  p->dataType = cmd->getCommandName();
  tmp = cmd->getCommandArg();
  i = -1;
  while (tmp[++i] != 0)
    p->data[i] = tmp[i];
  p->data[i] = 0;
  p->dataLength = tmp.size() + 4;
  i = -1;
  while (++i != p->dataLength)
    ret[i] = reinterpret_cast<char *>(p)[i];
  ret[i] = 0;
  delete(p);
  return (ret);
}

IEntity		*Serialize::unserializeEntity(char *data)
{
  return (NULL);
}

ICommand	*Serialize::unserializeCommand(char *data)
{
  return (NULL);
}
