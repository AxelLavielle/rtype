#pragma once

#include "Room.hh"
#include "Player.hh"
#include "Serialize.hh"

class Game
{
public:
	Game();
	~Game();

	void updateGame(const Room &);
};
