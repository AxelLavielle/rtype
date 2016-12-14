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

class Game
{
public:
	Game();
	~Game();
	int launch();
	void setGraph(IGraphManager * graph);
	void setEvent(IEventManager * event);
private:
	IGraphManager				*_graph;
	IEventManager				*_event;
	CmdManager					_cmd;
	std::vector<IGUIElement* >	_guiElement;
	int							_dificulty;
	std::pair<int, int>			_size;
	SFMLSound					_soundManager;
	Sound						_musicStage1;

	void createUI();
	void drawUi();
};

