#pragma once


#ifdef _WIN32
#include <Windows.h>
#endif
#include <string>
#include <vector>
#include <stdexcept>
#include "Room.hh"

class RoomManager
{
private:
	std::vector<Room>	_roomList;
	//ThreadPool			_threadPool;
	//DLManager				_dlManager;

public:
	RoomManager();
	~RoomManager();

	int					addRoom(const std::string &);
	bool				removeRoom(const int);
	Room				&getRoomByName(const std::string &);
	Room				&getRoomById(const int);
	std::vector<Room>	&getRoomList();
	std::string			getRoomListString() const;
	bool				addClientToRoom(ServerClient *, const std::string &);
	bool				addClientToRoom(ServerClient *, int);
	std::vector<Room>	getRoomsReady() const;
};
