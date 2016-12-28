#include "Game.hh"

Game::Game() : _map(150)
{
	_currentXMin = 0;
	_currentXMax = 150;
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

	it = clients.begin();
	i = 0;
	while (it != clients.end())
	{
		IEntity		*player;
	
		it2 = clients.begin();
		player = new Player(10 + (i * 10), 10 + (i * 20));
		(*it)->setPlayer(player);
		_map.setEntity(player);
		while (it2 != clients.end())
		{
			if (player)
			{
				std::cout << "Send initial info to " << (*it)->getTCPSocket() << std::endl;
				msg = Serialize::serialize(player);
				(*it2)->addUDPDataToSend(msg);
				delete (msg);
			}
			++it2;
		}
		i++;
		++it;
	}

	
	//IEntity *wall = new Barrier(0, NB_CELLS_Y);
	//_map.setEntity(wall);
	IEntity *wall1 = new Barrier(50, 50);
	_map.setEntity(wall1);

	IEntity *wall2 = new Barrier(50, 55);
	_map.setEntity(wall2);

	IEntity *missile = new Missile(30, 30);
	_map.setEntity(missile);

}

void	Game::manageInput(ServerClient *client)
{
	std::vector<InputCmd>			vInputs;
	std::vector<InputCmd>::iterator	it;
	IEntity							*player;
	int								newX;
	int								newY;
	vInputs = client->getInputs();
	it = vInputs.begin();
	player = client->getPlayer();
	while (it != vInputs.end())
	{
//		std::cout << "Player sent key [" << it->getKey() << "]" << std::endl;

		//TODO IF OUTSIDE MAP !

		newX = player->getPosX();
		newY = player->getPosY();
		
		if (it->getKey() == "UP" || it->getKey() == "DOWN")
			newY = (it->getKey() == "UP") ? (newY - 1) : (newY + 1);
		else if (it->getKey() == "RIGHT" || it->getKey() == "LEFT")
			newX = (it->getKey() == "RIGHT") ? (newX + 1) : (newX - 1);
		
		if (newX > _currentXMin && newX < _currentXMax && newY > 0 && newY < NB_CELLS_Y)
		{
			player->setPosX(newX);
			player->setPosY(newY);
		}
		//if (it->getKey() == "UP" || it->getKey() == "DOWN")
		//	player->setPosY((it->getKey() == "UP") ? (player->getPosY() - 1) : (player->getPosY() + 1));
		//else if (it->getKey() == "RIGHT" || it->getKey() == "LEFT")
		//	player->setPosX((it->getKey() == "RIGHT") ? (player->getPosX() + 1) : (player->getPosX() - 1));

		player->refresh();
		++it;
	}
	client->setPlayer(player);
}

void										Game::updateGame(std::vector<ServerClient *> &clients)
{
	//std::vector<ServerClient *>::iterator	it;
	//std::vector<ServerClient *>::iterator	it2;
	//char									*msg;
	//IEntity									*player;

	//it = clients.begin();
	//while (it != clients.end())
	//{
	//	it2 = clients.begin();
	//	manageInput(*it);
	//	player = (*it)->getPlayer();
	//	(*it)->clearInput();
	//	while (it2 != clients.end())
	//	{
	//		if (player)
	//		{
	//			msg = Serialize::serialize(player);
	//			(*it2)->addUDPDataToSend(msg);
	//			delete (msg);
	//		}
	//		++it2;
	//	}
	//	++it;
	//}


	updatePlayers(clients);

	////updateEntities();
	_map.refresh();
	sendEntitiesToClients(clients);
	
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
	std::vector<IEntity *>					entitiesToSend;
	std::vector<IEntity *>::iterator		itMap;
	std::vector<ServerClient *>::iterator	itClients;
	char									*msg;

	entitiesToSend = _map.getEntities(_currentXMin, _currentXMax);
	//std::cout << "[Game] : Sending [" << entitiesToSend.size() << "] Entities" << std::endl;
	itMap = entitiesToSend.begin();
	while (itMap != entitiesToSend.end())
	{
		itClients = clients.begin();
		while (itClients != clients.end())
		{
			msg = Serialize::serialize(*itMap);
			(*itClients)->addUDPDataToSend(msg);
			delete (msg);
			itClients++;
		}
		itMap++;
	}
	
}

void		Game::updateEntities()
{
	int		x;
	int		y;
	IEntity *currentEntity;

	//std::cout << "[Game] : Updating Entities" << std::endl;
	x = _currentXMin;
	y = 0;
	while (y < NB_CELLS_Y)
	{
		while (x < _currentXMax)
		{
			if ((currentEntity = _map(x, y)) != NULL && currentEntity->getType() != rtype::PLAYER)
			{
				currentEntity->update();
			}
			x++;
		}
		x = _currentXMin;
		y++;
	}
}
