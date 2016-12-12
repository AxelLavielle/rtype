#pragma once

#include "IGraphManager.hpp"
#include "IEventManager.hpp"

class InputBox
{
public:
	InputBox(IGraphManager *graph, IEventManager *event, const Rect &rect);
	~InputBox();
	InputBox();
	std::string getText() const;
	bool getInput();
	bool draw();
	void setGraph(IGraphManager *graph);
	void setEvent(IEventManager *event);

private:
	Rect			_rect;
	IGraphManager	*_graph;
	IEventManager	*_event;
	std::string		_key;
};

