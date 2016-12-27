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
#include "PausePage.hh"
#include "ASocketClient.hh"
#include "ThreadPool.hh"

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
	void setId(const int id);
	void setNbPlayer(const int nb);

private:
	IGraphManager				*_graph;
	IEventManager				*_event;
	CmdManager					_cmdManager;
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
	int							_id;
	std::string					_playerName;
	int							_nbPlayer;
	std::string					_mode;

	bool initSocket();
	void initGraphElements();
	void manageEntity();
};

