#pragma once

#include "Player.hh"
#include "Serialize.hh"
#include "ServerClient.hh"
#include "InputCmd.hh"

class Game
{
public:
	Game();
	~Game();

	void init(std::vector<ServerClient *> &);
	void updateGame(std::vector<ServerClient *> &);

private:
	void manageInput(ServerClient *client);
};
