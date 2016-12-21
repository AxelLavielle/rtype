#include "Game.hh"

Game::Game()
{
}

Game::~Game()
{
}

void	Game::updateGame(const Room &room)
{
	std::vector<ServerClient *>::iterator	it;
	char									*msg;

	it = room.getClients().begin();
	while (it != room.getClients().end())
	{
		AEntity *player = new Player ((*it)->getPlayerName());

		msg = Serialize::serialize(player);
		(*it)->addUDPDataToSend(msg);
		it++;
	}
}