#pragma once

#include "Player.hh"
#include "Serialize.hh"
#include "ServerClient.hh"
#include "InputCmd.hh"
#include "Wave.hh"

#define MISSILE_COOLDOWN	(10)

class Game
{
public:
	Game(DlManager *);
	~Game();

	void	init(std::vector<ServerClient *> &, const int);
	bool	updateGame(std::vector<ServerClient *> &);

private:
	int						_currentWall;
	std::vector<IEntity *>	_entityList;
	Wave					*_currentWave;
	int						_currentTime;
	DlManager				*_dlManager;
	IEntity					*_bossEntity;
	bool					_gameRunning;
	int						_roomId;
	int						_nbWaves;
	bool					_bossWave;

	void	manageInput(ServerClient *client);
	void	updateEntities();
	void	sendEntitiesToClients(std::vector<ServerClient *> &);
	void	updatePlayers(std::vector<ServerClient *> &);
	void	shootMissile(const int, const int, const int);
	void	addEntity(IEntity *);
	void	deleteEntities();
	void	addWalls(const int);
	void	checkCollisions();
	void	refreshWave();
};
