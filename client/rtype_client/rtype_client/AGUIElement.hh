#pragma once

#include "IGUIElement.hpp"

class AGUIElement :
	public IGUIElement
{
public:
	AGUIElement();
	AGUIElement(IGraphManager *graph, IEventManager *event, const Rect & rect);
	virtual ~AGUIElement();
	virtual bool draw() = 0;
	virtual bool click() = 0;
	virtual bool over() = 0;
	virtual void setGraph(IGraphManager * graph);
	virtual void setEvent(IEventManager * event);
	virtual void setPos(const Rect & rect);
	virtual Rect getPos() const;
	virtual void setBackgroundColor(const Color & color);
	virtual void setBackgroundColorOver(const Color & color);
	virtual void setBackgroundSprite(const std::string & path);
	virtual void setBackgroundOverSprite(const std::string & path);
	virtual void setTransparentColor(const Color & color);
protected:
	IGraphManager	*_graph;
	IEventManager	*_event;
	Rect			_rect;
	Color			_backgroundColor;
	Color			_backgroundColorOver;
	std::string		_backgroundSprite;
	std::string		_backgroundOverSprite;
	Color			_transparantColor;
};

