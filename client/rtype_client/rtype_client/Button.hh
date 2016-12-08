#pragma once

#include <iostream>
#include "IGraphManager.hpp"
#include "IEventManager.hpp"

class Button
{
public:
	Button(IGraphManager *graph, IEventManager *event, const Rect &rect, const std::string &txt);
	~Button();
	virtual bool draw();
	bool over();
	bool click();
	void setBackgroundColor(const Color & color);
	void setTextPos(const int &x, const int &y);
	void setTextSize(const int &size);
private:
	IGraphManager		*_graph;
	IEventManager		*_event;
	Rect				_rect;
	std::string			_txt;
	Color				_backgroundColor;

	int					_textSize;
	int					_posXText;
	int					_posYText;
	bool				_over;
};