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

	it = clients.begin();
	i = 0;
	while (it != clients.end())
	{
		IEntity		*player;
	
		it2 = clients.begin();
		player = new Player((*it)->getPlayerName());
		player->setLife(100);
		player->setPosX(400 + (i * 10));
		player->setPosY(500);
		player->setHeight(100);
		player->setWidth(100);
		player->setSpeedX(1);
		player->setSpeedY(1);
		player->setSpriteRepo("/res/img/");
		player->setType(rtype::PLAYER);
		(*it)->setPlayer(player);
		while (it2 != clients.end())
		{
			if (it != it2 && player)
				(*it2)->addUDPDataToSend(Serialize::serialize(player));
			++it2;
		}
		i++;
		++it;
	}
}

void	Game::manageInput(ServerClient *client)
{
	std::vector<InputCmd>::iterator	it;
	IEntity							*player;

	it = client->getInputs().begin();
	player = client->getPlayer();
	while (it != client->getInputs().end())
	{
		if (it->getKey() == "UP")
			player->setPosY(player->getPosY() - 10);
		else if (it->getKey() == "DOWN")
			player->setPosY(player->getPosY() + 10);
		else if (it->getKey() == "RIFHT")
			player->setPosX(player->getPosX() + 10);
		else if (it->getKey() == "LEFT")
			player->setPosX(player->getPosX() - 10);
		++it;
	}
	client->setPlayer(player);
}

void	Game::updateGame(std::vector<ServerClient *> &clients)
{
	std::vector<ServerClient *>::iterator	it;
	std::vector<ServerClient *>::iterator	it2;
	char									*msg;
	IEntity									*player;

	it = clients.begin();
	while (it != clients.end())
	{
		it2 = clients.begin();
		manageInput(*it);
		player = (*it)->getPlayer();
		(*it)->clearInput();
		while (it2 != clients.end())
		{
			if (it != it2 && player)
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
