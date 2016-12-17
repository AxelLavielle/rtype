#pragma once

#include "SFML.hh"
#include "SFMLEvent.hh"
#include "Menu.hh"
#include "Game.hh"
#include "CmdManager.hh"
 
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
	SocketClientTCP		*_socket;
	CmdManager			_cmdManager;

	bool initSocket();
	bool initGraph();
};

