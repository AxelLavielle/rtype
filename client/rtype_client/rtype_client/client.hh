#pragma once

#include "SFML.hh"
#include "SFMLEvent.hh"
#include "Menu.hh"
#include "Game.hh"

class Client
{
public:
	Client();
	~Client();
	bool launch();
private:
	IGraphManager		*_graph;
	IEventManager		*_event;
	IMenu				*_menu;
};

