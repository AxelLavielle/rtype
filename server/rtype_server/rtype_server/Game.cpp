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
		player = (*it)->getPlayer();
		while (it2 != clients.end())
		{
			if (it != it2)
				(*it2)->addUDPDataToSend(Serialize::serialize(player));
			++it2;
		}
		i++;
		++it;
	}
}

void	Game::updateGame(std::vector<ServerClient *> &clients)
{
	std::vector<ServerClient *>::iterator	it;
	char									*msg;
	static int x = 50;
	static int y = 100;

	if (clients.size() == 0)
		return;
	it = clients.begin();
	while (it != clients.end())
	{
		AEntity *player = new Player ((*it)->getPlayerName());
		player->setPosX(x);
		player->setPosY(y);
		player->setSpriteRepo("/res/img");
		Player	*test;

		//std::cout << "Add Player : " << player->getName() << std::endl;
		msg = Serialize::serialize(player);
		(*it)->addUDPDataToSend(msg);
		delete(player);
		/*test = static_cast<Player *>(Serialize::unserializeEntity(msg));
		std::cout << "Test serialize entity " << test->getPosX() << " " << test->getPosY() << std::endl;
		*/
		delete(msg);
		//delete(test);
		it++;
	}
	x++;
	if (y < 700)
		y++;
	else if (y > 700)
		y--;
}