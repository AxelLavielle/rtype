#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include "Room.hh"

class RoomManager
{
private:
	std::vector<Room>	_roomList;
	DlManager		*_dlManager;

public:
	RoomManager();
	~RoomManager();

  void				setDlManager(DlManager *);
	int					addRoom(const std::string &);
	bool				removeRoom(const int);
	Room				&getRoomByName(const std::string &);
	Room				*getRoomById(const int);
	std::vector<Room>	&getRoomList();
	bool				addClientToRoom(ServerClient *, const std::string &);
	bool				addClientToRoom(ServerClient *, int);
	bool				removeClientFromRoom(ServerClient *, const int);
	std::vector<Room>	getRoomsReadyToLaunch() const;
	std::vector<Room>	getRoomsReadyToPlay() const;
};
