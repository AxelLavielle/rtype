#pragma once

#include <vector>
#include <sstream>
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
	int click();

private:
	void drawButton();

	IGraphManager				*_graph;
	IEventManager				*_event;
	std::vector<std::string>	_elements;
	std::vector<Button>			_buttons;
	Button						_nextButton;
	Button						_prevButton;
	Rect						_rect;
	unsigned int				_height;
	int							_currentPage;
};

