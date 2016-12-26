#include "Game.hh"

Game::Game()
{
}

Game::~Game()
{
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