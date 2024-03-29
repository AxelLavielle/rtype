#include "Game.hh"

Game::Game(DlManager *dlM)
{
  _dlManager = dlM;
	_currentWall = 0;
}

Game::~Game()
{
}

void Game::init(std::vector<ServerClient*> &clients, const int id)
{
	unsigned int							i;
	std::vector<ServerClient *>::iterator	it;
	std::vector<ServerClient *>::iterator	it2;
	char									*msg;

	std::cout << "INITIALIZATION GAME" << std::endl;
	_roomId = id;
	it = clients.begin();
	i = 0;
	while (it != clients.end())
	{
		IEntity		*player;

		it2 = clients.begin();
		player = new Player(10 + (i * 10), 10 + (i * 20), i + 1, (*it)->getPlayerName());
		(*it)->setPlayer(player);
		addEntity(player);
		while (it2 != clients.end())
		{
			if (player)
			{
				std::cout << "Send initial info to " << (*it)->getTCPSocket() << std::endl;
				msg = Serialize::serialize(player);
				(*it2)->addUDPDataToSend(msg);
				delete[] msg;
			}
			it2++;
		}
		i++;
		it++;
	}

	addWalls(0);
	_currentWave = new Wave(5, _dlManager);
	_currentWave->generate();
	_currentTime = 0;
	_bossEntity = NULL;
	_gameRunning = true;
	_nbWaves = 0;
	_bossWave = false;
}

void								Game::shootMissile(const int x, const int y, const int idPlayer)
{
	IEntity *missile = new Missile(x, y, idPlayer);
	addEntity(missile);
}

void								Game::shootSuperMissile(const int x, const int y, const int idPlayer)
{
	IEntity *missile = new SuperMissile(x, y, idPlayer);
	addEntity(missile);
}

void								Game::addEntity(IEntity *newEntity)
{
	_entityList.push_back(newEntity);
}

void								Game::manageInput(ServerClient *client)
{
	std::vector<InputCmd>			vInputs;
	std::vector<InputCmd>::iterator	it;
	Player							*player;
	int								newX;
	int								newY;
	vInputs = client->getInputs();
	it = vInputs.begin();
	player = static_cast<Player *>(client->getPlayer());
	while (it != vInputs.end())
	{
		newX = player->getPosX();
		newY = player->getPosY();

		//std::cout << "Player input {" << it->getKey() << "}" << std::endl;

		if (it->getKey() == "UP" || it->getKey() == "DOWN")
			newY = (it->getKey() == "UP") ? (newY - 1) : (newY + 1);
		else if (it->getKey() == "RIGHT" || it->getKey() == "LEFT")
			newX = (it->getKey() == "RIGHT") ? (newX + 1) : (newX - 1);
		else if (it->getKey() == "SHOOT" && player->getMissileCooldown() <= 0)
		{
			shootMissile(newX + player->getWidth(), newY + player->getHeight() / 2, player->getIdPlayer());
			player->setMissileCooldown(MISSILE_COOLDOWN);
		}
		else if (it->getKey() == "SUPERSHOOT" && player->getNbSuperShoot() > 0)
		{
			shootSuperMissile(newX + player->getWidth(), newY + player->getHeight() / 2, player->getIdPlayer());
			player->setNbSuperShoot(player->getNbSuperShoot() - 1);
		}
		if (newX > 0 && newX < NB_CELLS_X && newY > 0 && newY < NB_CELLS_Y)
		{
			player->setPosX(newX);
			player->setPosY(newY);
		}
		player->setMissileCooldown(player->getMissileCooldown() - 1);
		player->refresh();
		it++;
	}
	client->setPlayer(player);
}

bool			Game::updateGame(std::vector<ServerClient *> &clients)
{
	updatePlayers(clients);

	if (_currentWall < NB_CELLS_X - 1)
		addWalls(_currentWall);

	refreshWave();

	updateEntities();

	checkCollisions();

	sendEntitiesToClients(clients);

	deleteEntities();

	_currentTime++;
	_currentWall--;

	return (_gameRunning);
}

void										Game::updatePlayers(std::vector<ServerClient *> &clients)
{
	std::vector<ServerClient *>::iterator	it;
	unsigned int										nbDeadPlayers;

	nbDeadPlayers = 0;
	it = clients.begin();
	while (it != clients.end())
	{
		if ((*it)->getPlayer()->isDead() == false)
		{
			manageInput(*it);
			(*it)->clearInput();
		}
		else
		{
			(*it)->getPlayer()->setPosX(-100);
			(*it)->getPlayer()->setPosY(-100);
			(*it)->getPlayer()->refresh();
			nbDeadPlayers++;
		}
		it++;
	}
	if (nbDeadPlayers == clients.size())
		_gameRunning = false;
}

void										Game::sendEntitiesToClients(std::vector<ServerClient *> &clients)
{
	std::vector<IEntity *>::iterator		itMap;
	std::vector<ServerClient *>::iterator	itClients;
	char									*msg;

	itMap = _entityList.begin();
	while (itMap != _entityList.end())
	{
		msg = Serialize::serialize(*itMap);
		itClients = clients.begin();
		while (itClients != clients.end())
		{
			(*itClients)->addUDPDataToSend(msg);
			itClients++;
		}
		delete[] msg;
		itMap++;
	}
}

void									Game::updateEntities()
{
	std::vector<IEntity *>::iterator	it;

	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if ((*it)->getType() != rtype::PLAYER)
		{
			(*it)->update();
			if (((*it)->getPosX() > NB_CELLS_X && (*it)->getType() == rtype::MISSILE)
				|| (*it)->getPosX() + (*it)->getWidth() < 0)
			{
				(*it)->setDead(true);
				(*it)->refresh();
			}
		}
		it++;
	}
}

void	Game::deleteEntities()
{
	std::vector<IEntity *>::iterator	it;

	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if ((*it)->isDead() && !IS_PLAYER(*it))
		{
			if ((*it) == _bossEntity)
				_gameRunning = false;
			delete (*it);
			it = _entityList.erase(it);
		}
		else
			it++;
	}
}

void	Game::addWalls(const int startX)
{
	int x;

	x = startX;
	while (x < NB_CELLS_X)
	{
		IEntity *wall = new Barrier(x, -5);
		addEntity(wall);

		IEntity *wall2 = new Barrier(x, NB_CELLS_Y - 3);
		addEntity(wall2);

		_currentWall = wall->getPosX() + wall->getWidth();
		x += wall->getWidth();
	}
}

void	Game::playerCollisions(IEntity *it, IEntity *itOther)
{
	if (IS_PLAYER(itOther))
		return;

	if (IS_WALL(itOther))
	{
		it->setLife(it->getLife() - itOther->getAttack());
		return;
	}

	if (IS_MISSILE(itOther) && IS_PLAYER_MISSILE(static_cast<Missile *>(itOther)))
		return;

	if (IS_MISSILE(itOther) && IS_MONSTER_MISSILE(static_cast<Missile *>(itOther)))
	{
		it->setLife(it->getLife() - itOther->getAttack());
		itOther->setDead(true);
		itOther->refresh();
	}
	if (IS_MONSTER(itOther))
	{
		it->setLife(it->getLife() - itOther->getAttack());
		itOther->setLife(itOther->getLife() - it->getAttack());
	}
}

void	Game::monsterCollisions(IEntity *it, IEntity *itOther)
{
	if (IS_PLAYER(itOther))
	{
		it->setLife(it->getLife() - itOther->getAttack());
		itOther->setLife(itOther->getLife() - it->getAttack());
	}

	if (IS_WALL(itOther))
		return;

	if (IS_MISSILE(itOther) && IS_PLAYER_MISSILE(static_cast<Missile *>(itOther)))
	{
		it->setLife(it->getLife() - itOther->getAttack());
		itOther->setDead(true);
		itOther->refresh();
	}

	if (IS_MISSILE(itOther) && IS_MONSTER_MISSILE(static_cast<Missile *>(itOther)))
		return;

	if (IS_MONSTER(itOther))
		return;
}

void	Game::playerMissileCollisions(IEntity *it, IEntity *itOther)
{
	if (IS_PLAYER(itOther))
		return;

	if (IS_WALL(itOther))
	{
		it->setDead(true);
		it->refresh();
	}

	if (IS_MISSILE(itOther) && IS_PLAYER_MISSILE(static_cast<Missile *>(itOther)))
		return;

	if (IS_MISSILE(itOther) && IS_MONSTER_MISSILE(static_cast<Missile *>(itOther)))
	{
		it->setDead(true);
		it->refresh();
		itOther->setDead(true);
		itOther->refresh();
	}
	if (IS_MONSTER(itOther))
	{
		itOther->setLife(itOther->getLife() - it->getAttack());
		it->setDead(true);
		it->refresh();
		if (itOther->getName().find("Boss") == std::string::npos)
			addScoreToPlayer(static_cast<Missile *>(it)->getIdPlayer(), KILL_MONSTER_SCORE);
		else
			addScoreToPlayer(static_cast<Missile *>(it)->getIdPlayer(), KILL_BOSS_SCORE);
	}

}

void	Game::monsterMissileCollisions(IEntity *it, IEntity *itOther)
{
	if (IS_PLAYER(itOther))
	{
		itOther->setLife(itOther->getLife() - it->getAttack());
		it->setDead(true);
		it->refresh();
	}
	if (IS_WALL(itOther))
	{
		it->setDead(true);
		it->refresh();
	}

	if (IS_MISSILE(itOther) && IS_PLAYER_MISSILE(static_cast<Missile *>(itOther)))
	{
		it->setDead(true);
		it->refresh();
		itOther->setDead(true);
		itOther->refresh();
	}
	if (IS_MISSILE(itOther) && IS_MONSTER_MISSILE(static_cast<Missile *>(itOther)))
		return;
	if (IS_MONSTER(itOther))
		return;
}


void									Game::checkCollisions()
{
	std::vector<IEntity *>::iterator	it;
	std::vector<IEntity *>::iterator	itOther;

	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if (!IS_WALL(*it))
		{
			itOther = _entityList.begin();

			while (itOther != _entityList.end())
			{
				if (IS_COLLIDING(*it, *itOther))
				{
					if (IS_PLAYER(*it))
						playerCollisions(*it, *itOther);
					else if (IS_MONSTER(*it))
						monsterCollisions(*it, *itOther);
					else if (IS_MISSILE(*it) && IS_PLAYER_MISSILE(static_cast<Missile *>(*it)))
						playerMissileCollisions(*it, *itOther);
					else if (IS_MISSILE(*it) && IS_MONSTER_MISSILE(static_cast<Missile *>(*it)))
						monsterMissileCollisions(*it, *itOther);
				}

				itOther++;
			}
		}
		it++;
	}
}

void			Game::setNbWaves()
{
	std::vector<IEntity *>::iterator	it;

	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if (IS_PLAYER(*it))
		{
			(*it)->setWaveNumber(_nbWaves);
			addScoreToPlayer(static_cast<Player *>(*it)->getIdPlayer(), KILL_WAVE_SCORE);
			(*it)->refresh();
		}
		it++;
	}
}

void									Game::addScoreToPlayer(const int playerId, const int score)
{
	std::vector<IEntity *>::iterator	it;

	it = _entityList.begin();
	while (it != _entityList.end())
	{
		if (IS_PLAYER(*it) && static_cast<Player *>(*it)->getIdPlayer() == playerId)
		{
			(*it)->setScore((*it)->getScore() + score);
			(*it)->refresh();
		}
		it++;
	}
}

void									Game::refreshWave()
{
	std::vector<IEntity *>				entities;
	std::vector<IEntity *>::iterator	it;

	entities = _currentWave->getEntities(_currentTime);
	it = entities.begin();
	while (it != entities.end())
	{
		addEntity(*it);
		it++;
	}
	if (_currentWave->isOver() && _bossWave == false)
	  {
		if (_nbWaves >= 3)
		{
			if (DEBUG_MSG)
				std::cout << "---------------------------------------------ROOM [" << _roomId << "] GENERATING BOSS !!!" << std::endl;
			_bossEntity = _currentWave->generateBoss();
			_bossWave = true;
		}
	    else
		{
			if (DEBUG_MSG)
				std::cout << "Current Wave ROOM [" << _roomId << "]= [" << _nbWaves << "]" << std::endl;
			_currentWave->generate();
	    }
	    _nbWaves++;
		setNbWaves();
	  }
}
