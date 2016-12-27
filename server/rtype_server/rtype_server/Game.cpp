#include "Game.hh"

Game::Game()
{
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
		player = new Player((*it)->getPlayerName());
		player->setLife(100);
		player->setPosX(100 + (i * 100));
		player->setPosY(100);
		player->setHeight(30);
		player->setWidth(70);
		player->setSpeedX(1);
		player->setSpeedY(1);
		player->setSpriteRepo("/res/img/");
		player->setType(rtype::PLAYER);
		(*it)->setPlayer(player);
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
}

void	Game::manageInput(ServerClient *client)
{
	std::vector<InputCmd>			vInputs;
	std::vector<InputCmd>::iterator	it;
	IEntity							*player;

	vInputs = client->getInputs();
	it = vInputs.begin();
	player = client->getPlayer();
	while (it != vInputs.end())
	{
//		std::cout << "Player sent key [" << it->getKey() << "]" << std::endl;
		if (it->getKey() == "UP" || it->getKey() == "DOWN")
			player->setPosY((it->getKey() == "UP") ? (player->getPosY() - 10) : (player->getPosY() + 10));
		else if (it->getKey() == "RIGHT" || it->getKey() == "LEFT")
			player->setPosX((it->getKey() == "RIGHT") ? (player->getPosX() + 10) : (player->getPosX() - 10));
		++it;
	}
	client->setPlayer(player);
}

void										Game::updateGame(std::vector<ServerClient *> &clients)
{
	std::vector<ServerClient *>::iterator	it;
	std::vector<ServerClient *>::iterator	it2;
	char									*msg;
	IEntity									*player;

	it = clients.begin();
	while (it != clients.end())
	{
		it2 = clients.begin();
		while (it2 != clients.end())
		{
			if ((*it)->getPlayer())
			{
				std::cout << "Sending player (" << (*it)->getPlayer()->getPosX() << ", " << (*it)->getPlayer()->getPosY() << ")" << std::endl;
				msg = Serialize::serialize((*it)->getPlayer());
				(*it2)->addUDPDataToSend(msg);
				delete (msg);
			}
			it2++;
		}
		it++;
	}
	return;
	it = clients.begin();
	while (it != clients.end())
	{
		it2 = clients.begin();
		manageInput(*it);
		player = (*it)->getPlayer();
		(*it)->clearInput();
		while (it2 != clients.end())
		{
			if (player)
			{
				msg = Serialize::serialize(player);
				(*it2)->addUDPDataToSend(msg);
				delete (msg);
			}
			++it2;
		}
		++it;
	}
}
