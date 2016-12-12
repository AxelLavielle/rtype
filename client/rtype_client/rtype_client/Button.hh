#pragma once

#include <iostream>
#include "AGUIElement.hh"

class Button
{
public:
	Button(IGraphManager *graph, IEventManager *event, const Rect &rect, const std::string &txt);
	Button();
	~Button();
	virtual bool draw();
	bool over();
	bool click() const;
	void setBackgroundColor(const Color & color);
	void setBackgroundColorOver(const Color & color);
	void setTextPos(const int &x, const int &y);
	void setTextSize(const int &size);
	void setGraph(IGraphManager *graph);
	void setEvent(IEventManager *event);
	void setPos(const Rect & rect);
	void setText(const std::string &txt);
private:
	IGraphManager		*_graph;
	IEventManager		*_event;
	Rect				_rect;
	std::string			_txt;
	Color				_backgroundColor;
	Color				_backgroundColorOver;

	int					_textSize;
	int					_posXText;
	int					_posYText;
	bool				_over;
};