#include "Game.hh"

Game::Game()
{
	_currentXMin = 0;
	_currentXMax = 150;
	_entityList = new std::vector<IEntity *> ();
}

Game::~Game()
{
}

void Game::init(std::vector<ServerClient*> &clients)
{
	unsigned int							i;
	std::vector<ServerClient *>::iterator	it;
	std::vector<ServerClient *>::iterator	it2;
	char									*msg;

	std::cout << "INITIALIZATION GAME" << std::endl;
	it = clients.begin();
	i = 0;
	while (it != clients.end())
	{
		IEntity		*player;

		it2 = clients.begin();
		player = new Player(10 + (i * 10), 10 + (i * 20));
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
			++it2;
		}
		i++;
		++it;
	}

	IEntity *wall = new Barrier(50, 50);
	addEntity(wall);
	IEntity *wall2 = new Barrier(80, 50);
	addEntity(wall2);
	//_map.setEntity(wall);

}

void								Game::shootMissile(const int x, const int y)
{
	IEntity *missile = new Missile(x, y);
	addEntity(missile);
}

void								Game::addEntity(IEntity *newEntity)
{
	_entityList->push_back(newEntity);
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
//		std::cout << "Player sent key [" << it->getKey() << "]" << std::endl;

		newX = player->getPosX();
		newY = player->getPosY();

		if (it->getKey() == "UP" || it->getKey() == "DOWN")
			newY = (it->getKey() == "UP") ? (newY - 1) : (newY + 1);
		else if (it->getKey() == "RIGHT" || it->getKey() == "LEFT")
			newX = (it->getKey() == "RIGHT") ? (newX + 1) : (newX - 1);
		else if (it->getKey() == "SHOOT" && player->getMissileCooldown() <= 0)
		{
			shootMissile(newX + player->getWidth(), newY);
			player->setMissileCooldown(MISSILE_COOLDOWN);
		}
		if (newX > _currentXMin && newX < _currentXMax && newY > 0 && newY < NB_CELLS_Y)
		{
			player->setPosX(newX);
			player->setPosY(newY);
		}
		player->setMissileCooldown(player->getMissileCooldown() - 1);
		player->refresh();
		++it;
	}
	client->setPlayer(player);
}

void										Game::updateGame(std::vector<ServerClient *> &clients)
{
	updatePlayers(clients);

	updateEntities();

	sendEntitiesToClients(clients);

	deleteEntities();
	
	/*_currentXMin++;
	_currentXMax++;*/
}

void										Game::updatePlayers(std::vector<ServerClient *> &clients)
{
	std::vector<ServerClient *>::iterator	it;

	//std::cout << "[Game] : Updating Players" << std::endl;
	it = clients.begin();
	while (it != clients.end())
	{
		manageInput(*it);
		(*it)->clearInput();
		it++;
	}
}

void										Game::sendEntitiesToClients(std::vector<ServerClient *> &clients)
{
	std::vector<IEntity *>::iterator		itMap;
	std::vector<ServerClient *>::iterator	itClients;
	char									*msg;

	//std::cout << "[Game] : Sending [" << entitiesToSend.size() << "] Entities" << std::endl;
	itMap = _entityList->begin();
	while (itMap != _entityList->end())
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

void		Game::updateEntities()
{
	IEntity								*currentEntity;
	std::vector<IEntity *>::iterator	it;
	int	n = 0;

	//std::cout << "[Game] : Sending [" << entitiesToSend.size() << "] Entities" << std::endl;
	it = _entityList->begin();
	while (it != _entityList->end())
	{
		if ((*it)->getType() != rtype::PLAYER)
		{
			n++;
			std::cout << "[Game] : Updating Entity [" << (*it)->getId() << "]" << std::endl;
			(*it)->update();
			if ((*it)->getPosX() > _currentXMax)
			{
				(*it)->setDead(true);
				(*it)->refresh();
			}
		}
		it++;
	}
	
	if (n > 0)
		std::cout << "[Game] : Updated " << n << " Entities" << std::endl << std::endl;
}

void	Game::deleteEntities()
{
	std::vector<IEntity *>::iterator	it;

	it = _entityList->begin();
	while (it != _entityList->end())
	{
		if ((*it)->isDead())
		{
			delete (*it);
			it = _entityList->erase(it);
		}
		else
			it++;
	}
}