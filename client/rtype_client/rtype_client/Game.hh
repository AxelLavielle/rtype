#pragma once

#include <chrono>
#include <ctime>
#include <vector>
#include "IGraphManager.hpp"
#include "IEventManager.hpp"
#include "CmdManager.hh"
#include "AGUIElement.hh"
#include "RectDecor.hh"
#include "Sound.hh"
#include "SFMLSound.hh"
#include "InputCmd.hh"
#include "Serialize.hh"
#include "SocketClientUDP.hh"
#include "APage.hh"
#include "GUIPage.hh"
#include "ASocketClient.hh"

class Game
{
public:
	Game();
	~Game();
	int launch();
	void setGraph(IGraphManager * graph);
	void setEvent(IEventManager * event);
	void setIp(const std::string &ip);
	void setPort(const int port);

private:
	IGraphManager				*_graph;
	IEventManager				*_event;
	CmdManager					_cmd;
	std::vector<IGUIElement* >	_guiElement;
	int							_dificulty;
	std::pair<int, int>			_size;
	SFMLSound					_soundManager;
	Sound						_musicStage1;
	ICommand					*_input;
	Serialize					_serialize;
	ASocketClient				*_sock;
	APage						*_guiPage;
	PathFileManager				_fileManager;
	std::string					_ip;
	int							_port;
};

