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

	_roomList.push_back(new Room(idRoom, roomName));
	idRoom++;
	return (idRoom - 1);
}

bool							RoomManager::removeRoom(int roomId)
{
	std::vector<Room *>::iterator	it;

	it = _roomList.begin();
	while (it != _roomList.end())
	{
		if ((*it)->getId() == roomId)
		{
			_roomList.erase(it);
			return (true);
		}
		it++;
	}
	return (false);
}

Room									*RoomManager::getRoomByName(const std::string &roomName) const
{
	std::vector<Room *>::const_iterator	it;

	it = _roomList.begin();
	while (it != _roomList.end())
	{
		if ((*it)->getName().compare(roomName) == 0)
			return (*it);
		it++;
	}
	return (NULL);
}

Room									*RoomManager::getRoomById(int roomId) const
{
	std::vector<Room *>::const_iterator	it;

	it = _roomList.begin();
	while (it != _roomList.end())
	{
		if ((*it)->getId() == roomId)
			return (*it);
		it++;
	}
	return (NULL);
}

std::vector<Room *> RoomManager::getRoomList() const
{
	return (_roomList);
}

std::string			listClients(std::vector<ServerClient *> clientList)
{
	std::string		strClients;
	std::vector<ServerClient *>::const_iterator	itClient;

	itClient = clientList.begin();
	while (itClient != clientList.end())
	{
		strClients += "--------> ";
		strClients += std::to_string((*itClient)->getTCPSocket());
		strClients += "\n";
		itClient++;
	}
	return (strClients);
}
std::string								RoomManager::getRoomListString() const
{
	std::string							roomList;
	std::vector<Room *>::const_iterator	it;
	
	it = _roomList.begin();
	while (it != _roomList.end())
	{
		roomList += "Room ";
		roomList += std::to_string((*it)->getId());
		roomList += " : ";
		roomList += (*it)->getName();
		roomList += "\n";
		roomList += listClients((*it)->getClients());
		
		it++;
	}
	return (roomList);
}

bool		RoomManager::addClientToRoom(ServerClient *client, const std::string &name)
{
	Room	*room;

	if ((room = getRoomByName(name)) == NULL)
		return (false);
	room->addClient(client);
	return (true);
}

bool	RoomManager::addClientToRoom(ServerClient *client, int id)
{
	Room	*room;

	if ((room = getRoomById(id)) == NULL)
		return (false);
	room->addClient(client);
	if (client->getCurrentRoom() != NULL)
		client->getCurrentRoom()->removeClient(client);
	client->setCurrentRoom(room);

	return (true);
}
