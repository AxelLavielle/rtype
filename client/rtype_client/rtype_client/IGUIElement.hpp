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
	virtual void setBackgroundColor(const Color & color) = 0;
	virtual void setBackgroundColorOver(const Color & color) = 0;
	virtual void setBackgroundSprite(const std::string & path) = 0;
	virtual void setBackgroundOverSprite(const std::string & path) = 0;
	virtual void setTransparentColor(const Color & color) = 0;
	virtual Rect getPos() const = 0;
};
