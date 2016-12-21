#pragma once

#include	"ACommand.hh"

typedef std::pair<std::string, int>			RoomNameNbPlayer;
typedef std::pair<int, RoomNameNbPlayer>	RoomIdInfos;

class		ListRoomCmd : public ACommand
{
public:
  ListRoomCmd();
  virtual	~ListRoomCmd();

  virtual CmdName							getCommandName() const;
  virtual const std::string					getCommandArg() const;
  virtual void								setCommandArg(const std::string &);
  void										addRoom(const int, const std::string &, const int);
  RoomIdInfos								getRoom(const int index) const;
  std::vector<RoomIdInfos>					getAllRooms() const;

private:
	std::vector<RoomIdInfos>				_roomList;
};
