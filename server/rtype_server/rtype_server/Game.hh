#pragma once

#include "Player.hh"
#include "Serialize.hh"
#include "ServerClient.hh"
#include "InputCmd.hh"

#define NB_CELLS_Y			(80)
#define NB_CELLS_X			(160)
#define MISSILE_COOLDOWN	(10)

class Game
{
public:
	Game();
	~Game();

	void	init(std::vector<ServerClient *> &);
	void	updateGame(std::vector<ServerClient *> &);

private:
	int						*_currentWall;
	std::vector<IEntity *>	*_entityList;

	void	manageInput(ServerClient *client);
	void	updateEntities();
	void	sendEntitiesToClients(std::vector<ServerClient *> &);
	void	updatePlayers(std::vector<ServerClient *> &);
	void	shootMissile(const int, const int, const int);
	void	addEntity(IEntity *);
	void	deleteEntities();
	void	addWalls(const int);
	void	checkCollisions();
	void	addMonsters();
	void	addRedWave();


};
