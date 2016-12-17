#pragma once

#include <string>
#include <vector>
#include "Room.hh"

class RoomManager
{
private:
	std::vector<Room *> _roomList;

public:
	RoomManager();
	~RoomManager();

	int					addRoom(const std::string &);
	bool				removeRoom(int);
	Room				*getRoomByName(const std::string &) const;
	Room				*getRoomById(int) const;
	std::vector<Room *>	getRoomList() const;
	std::string			getRoomListString() const;
	bool				addClientToRoom(ServerClient *, const std::string &);
	bool				addClientToRoom(ServerClient *, int);
};