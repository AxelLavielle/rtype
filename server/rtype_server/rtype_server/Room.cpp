#include "Room.hh"

Room::Room(int id)
{
	_id = id;
}

Room::Room(int id, const std::string &name)
{
	_id = id;
	_name = name;
}

Room::~Room()
{
}

std::string				Room::getName() const
{
	return (_name);
}

void					Room::setName(const std::string &name)
{
	_name = name;
}

int						Room::getId() const
{
	return (_id);
}

void					Room::pauseGame()
{

}

bool					Room::addClient(const Client &client)
{
	_clients.push_back(client);
	return (true);
}