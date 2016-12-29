#pragma once

#include "Player.hh"
#include "Serialize.hh"
#include "ServerClient.hh"
#include "InputCmd.hh"
#include "Map.hh"

class Game
{
public:
	Game();
	~Game();

	void init(std::vector<ServerClient *> &);
	void updateGame(std::vector<ServerClient *> &);

private:
	int		_currentXMin;
	int		_currentXMax;
	Map		_map;

	void	manageInput(ServerClient *client);
	void	updateEntities();
	void	sendEntitiesToClients(std::vector<ServerClient *> &);
	void	updatePlayers(std::vector<ServerClient *> &);
	void	shootMissile(const int, const int);

};
