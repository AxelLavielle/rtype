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

protected:
	IGraphManager	*_graph;
	IEventManager	*_event;
	Rect			_rect;
};

