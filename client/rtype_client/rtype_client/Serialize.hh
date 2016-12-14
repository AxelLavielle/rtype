#pragame once

#include	"CmdEnum.hh"

class		Serialize
{
public:
  Serialize();
  char		*serialize(IEntity *);
  char		*serialize(ICommand *);
  IEntity	unserializeEntity(char *);
  ICommand	unserializeCommand(char *);
  ~Serialize();

private:
  char		*serializeChatInfo(ICommand*);
  char		*serializeRoomInfo(ICommand*);
  char		*serializeRoomList(ICommand*);
  char		*serializeEntity(ICommand*);
  char		*serializeInput(ICommand*);
  ICommand	*unserializeChatInfo(char*);
  ICommand	*unserializeRoomInfo(char*);
  ICommand	*unserializeRoomList(char*);
  ICommand	*unserializeEntity(char*);
  ICommand	*unserializeInput(char*);
};
