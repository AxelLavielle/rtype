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
	virtual void setBackgroundOverColor(const Color & color);
	virtual void setBackgroundSprite(const std::string & path);
	virtual void setBackgroundOverSprite(const std::string & path);
	virtual void setTransparentColor(const Color & color);
	virtual void setFontPath(const std::string & path);
	virtual std::string getTypeName() const;
protected:
	IGraphManager	*_graph;
	IEventManager	*_event;
	Rect			_rect;
	Color			_backgroundColor;
	Color			_backgroundOverColor;
	std::string		_backgroundSprite;
	std::string		_backgroundOverSprite;
	Color			_transparentColor;
	std::string		_fontPath;
	std::string		_typeName;
};

