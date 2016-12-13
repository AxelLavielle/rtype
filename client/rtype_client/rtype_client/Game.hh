#pragma once

#include <chrono>
#include <ctime>
#include <vector>
#include "IGraphManager.hpp"
#include "IEventManager.hpp"
#include "CmdManager.hh"
#include "AGUIElement.hh"
#include "RectDecor.hh"

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
	std::vector<AGUIElement* >	_guiElement;

	void createUI();
	void drawUi();
};

