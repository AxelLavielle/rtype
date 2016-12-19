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
	std::vector<Room>::const_iterator	it;
	
	it = _roomList.begin();
	while (it != _roomList.end())
	{
		roomList += "Room ";
		roomList += std::to_string((*it).getId());
		roomList += " : ";
		roomList += (*it).getName();
		roomList += "\n";
		roomList += listClients((*it).getClients());
		
		it++;
	}
	return (roomList);
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
