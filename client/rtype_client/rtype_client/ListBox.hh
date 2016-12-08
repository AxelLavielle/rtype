#pragma once

#include <vector>
#include "Button.hh"
#include "IGraphManager.hpp"
#include "IEventManager.hpp"

class ListBox
{
public:
	ListBox(IGraphManager *graph, IEventManager *event, const Rect &rect);
	~ListBox();
	bool draw();
	void setElements(const std::vector<std::string> &elements);

private:
	void drawButton();

	IGraphManager				*_graph;
	IEventManager				*_event;
	std::vector<std::string>	_elements;
	std::vector<Button>			_buttons;
	Rect						_rect;
	unsigned int				_height;
};

