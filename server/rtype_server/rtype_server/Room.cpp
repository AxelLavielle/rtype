#include "Room.hh"

Room::Room(const int id)
{
	_id = id;
	_readyToLaunch = false;
	_readyToPlay = false;
}

Room::Room(const int id, const std::string &name)
{
	_id = id;
	_name = name;
	_readyToLaunch = false;
	_readyToPlay = false;
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

bool					Room::addClient(ServerClient *client)
{
	if (_clients.size() >= MAX_PLAYERS)
		return (false);
	_clients.push_back(client);
	return (true);
}

bool										Room::removeClient(ServerClient *client)
{
	std::vector<ServerClient *>::iterator	it;

	it = _clients.begin();
	while (it != _clients.end())
	{
		if ((*it) == client)
		{
			_clients.erase(it);
			return (true);
		}
		it++;
	}
	return (false);
}

std::vector<ServerClient *>		Room::getClients() const
{
	return (_clients);
}

int								Room::getNbClients() const
{
	return (_clients.size());
}

int												Room::getNbClientsReady() const
{
	std::vector<ServerClient *>::const_iterator	it;
	int											nb;

	nb = 0;
	it = _clients.begin();
	while (it != _clients.end())
	{
		if ((*it)->isReady())
			nb++;
		it++;
	}
	return (nb);
}

int												Room::getNbClientsUDPConnected() const
{
	std::vector<ServerClient *>::const_iterator	it;
	int											nb;

	nb = 0;
	it = _clients.begin();
	while (it != _clients.end())
	{
		if ((*it)->getAddrUDP() != NULL)
			nb++;
		it++;
	}
	return (nb);
}

void			Room::setReadyToLaunch(const bool launch)
{
	_readyToLaunch = launch;
}

bool			Room::isReadyToLaunch() const
{
	return (_readyToLaunch);
}

void			Room::setReadyToPlay(const bool launch)
{
	_readyToLaunch = launch;
}

bool			Room::isReadyToPlay() const
{
	return (_readyToPlay);
}