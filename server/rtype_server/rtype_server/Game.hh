#pragma once

#include "Player.hh"
#include "Serialize.hh"
#include "ServerClient.hh"
#include "InputCmd.hh"
#include "Wave.hh"

#define MISSILE_COOLDOWN			(10)
#define KILL_MONSTER_SCORE			(100)

#define IS_PLAYER(elem)				((elem)->getType() == rtype::PLAYER)
#define IS_WALL(elem)				((elem)->getType() == rtype::BARRIER)
#define IS_MONSTER(elem)			((elem)->getType() == rtype::MONSTER)
#define IS_MISSILE(elem)			((elem)->getType() == rtype::MISSILE)
#define IS_PLAYER_MISSILE(elem)		((elem)->getIdPlayer() != 0)
#define IS_MONSTER_MISSILE(elem)	((elem)->getIdPlayer() == 0)
#define IS_COLLIDING(e1, e2)		((e1)->isColliding((e2)->getCollisionBox()))

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
	void	shootSuperMissile(const int, const int, const int);
	void	addEntity(IEntity *);
	void	deleteEntities();
	void	addWalls(const int);
	void	checkCollisions();
	void	playerMissileCollisions(IEntity *, IEntity *);
	void	monsterMissileCollisions(IEntity *, IEntity *);
	void	monsterCollisions(IEntity *, IEntity *);
	void	playerCollisions(IEntity *, IEntity *);
	void	refreshWave();
	void	setNbWaves();
	void	addScoreToPlayer(const int, const int);
};
