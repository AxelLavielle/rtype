#include "RoomManager.hh"

RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
}

int								RoomManager::addRoom(const std::string &roomName)
{
	static int					idRoom = 0;

	_roomList.push_back(Room(idRoom, roomName));
	idRoom++;
	return (idRoom - 1);
}

bool							RoomManager::removeRoom(const int roomId)
{
	std::vector<Room>::iterator	it;

	it = _roomList.begin();
	while (it != _roomList.end())
	{
		if ((*it).getId() == roomId)
		{
			_roomList.erase(it);
			return (true);
		}
		it++;
	}
	return (false);
}

Room									&RoomManager::getRoomByName(const std::string &roomName)
{
	std::vector<Room>::iterator	it;

	it = _roomList.begin();
	while (it != _roomList.end())
	{
		if ((*it).getName().compare(roomName) == 0)
			return (*it);
		it++;
	}
	throw (std::runtime_error("No such room"));
}

Room									&RoomManager::getRoomById(const int roomId)
{
	std::vector<Room>::iterator	it;

	it = _roomList.begin();
	while (it != _roomList.end())
	{
		if ((*it).getId() == roomId)
			return (*it);
		it++;
	}
	throw (std::runtime_error("No such room"));
}

std::vector<Room> &RoomManager::getRoomList()
{
	return (_roomList);
}

bool		RoomManager::addClientToRoom(ServerClient *client, const std::string &name)
{
	try
	{
		getRoomByName(name);
	}
	catch (const std::exception &error)
	{
		std::cerr << "############ " << error.what() << std::endl;
		return (false);
	}
	
	if (getRoomByName(name).addClient(client) == false)
		return (false);

	if (client->getCurrentRoom() != -1)
	{
		try
		{
			getRoomById(client->getCurrentRoom());
			getRoomById(client->getCurrentRoom()).removeClient(client);
		}
		catch (const std::exception &error)
		{
			std::cerr << "############ " << error.what() << std::endl;
		}
	}

	client->setCurrentRoom(getRoomByName(name).getId());

	return (true);
}

bool		RoomManager::addClientToRoom(ServerClient *client, const int id)
{
	try
	{
		getRoomById(id);
	}
	catch (const std::exception &error)
	{
		std::cerr << "############ " << error.what() << std::endl;
		return (false);
	}

	if (getRoomById(id).addClient(client) == false)
		return (false);

	if (client->getCurrentRoom() != - 1)
	{
		try
		{
			getRoomById(client->getCurrentRoom());
			getRoomById(client->getCurrentRoom()).removeClient(client);
		}
		catch (const std::exception &error)
		{
			std::cerr << "############ " << error.what() << std::endl;
		}

	}
	client->setCurrentRoom(id);
	return (true);
}
#include <Windows.h>

std::vector<Room>						RoomManager::getRoomsReady() const
{
	std::vector<Room>					roomsReady;
	std::vector<Room>::const_iterator	it;

	if (_roomList.size() == 0)
		return (roomsReady);
	
	it = _roomList.begin();
	while (it != _roomList.end())
	{
		//std::cout << "Room [" << (*it).getName() << "] : " << (*it).getNbClientsReady() << std::endl;
		if ((*it).getNbClients() > 0 && (*it).getNbClients() == (*it).getNbClientsReady())
			roomsReady.push_back((*it));
		it++;
	}
	return (roomsReady);
}
