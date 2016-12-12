#pragma once

#include "IGraphManager.hpp"
#include "IEventManager.hpp"

class IGUIElement
{
public:
	virtual ~IGUIElement() {}
	virtual bool draw() = 0;
	virtual bool over() = 0;
	virtual bool click() = 0;
	virtual void setGraph(IGraphManager * graph) = 0;
	virtual void setEvent(IEventManager * event) = 0;
	virtual void setPos(const Rect & rect) = 0;
};