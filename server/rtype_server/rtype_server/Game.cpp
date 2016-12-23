#include "Game.hh"

Game::Game()
{
}

Game::~Game()
{
}

void	Game::updateGame(const Room &room)
{
	std::vector<ServerClient *>				clients;
	std::vector<ServerClient *>::iterator	it;
	char									*msg;

	if ((clients = room.getClients()).size() == 0)
		return;
	it = clients.begin();
	while (it != clients.end())
	{
		AEntity *player = new Player ((*it)->getPlayerName());
		player->setPosX(50);
		player->setPosY(100);
		//Player	*test;

		//std::cout << "Add Player : " << player->getName() << std::endl;
		msg = Serialize::serialize(player);
		(*it)->addUDPDataToSend(msg);
		delete(msg);
		delete(player);
		//test = static_cast<Player *>(Serialize::unserializeEntity(msg));
		//std::cout << "Test serialize entity " << test->getName() << std::endl;
		it++;
	}
}