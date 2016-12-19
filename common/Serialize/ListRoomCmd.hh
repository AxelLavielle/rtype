#pragma once

#include	"ACommand.hh"

class		ListRoomCmd : public ACommand
{
public:
  ListRoomCmd();
  virtual	~ListRoomCmd();

  virtual CmdName							getCommandName() const;
  virtual const std::string					getCommandArg() const;
  virtual void								setCommandArg(const std::string &);
  void										addRoom(const std::string &, const int);
  std::pair<std::string, int>				getRoom(const int index) const;
  std::vector<std::pair<std::string, int>>	getAllRooms() const;


protected:
	std::vector<std::pair<std::string, int>> _roomList;
};
