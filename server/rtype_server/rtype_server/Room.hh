#pragma once

#include "ServerClient.hh"
#include <string>
#include <vector>
class ServerClient;

#define MAX_PLAYERS	(4)

class Room
{
public:
	Room(int);
	Room(int, const std::string &);
	~Room();

	std::string					getName() const;
	void						setName(const std::string &);
	int							getId() const;
	void						pauseGame();
	bool						addClient(ServerClient *);
	bool						removeClient(ServerClient *);
	std::vector<ServerClient *> getClients() const;
	int							getNbClients() const;

private:
	std::string					_name;
	int							_id;
	std::vector<ServerClient *>	_clients;
};

