#include "AGUIElement.hh"

AGUIElement::AGUIElement()
{
	_graph = NULL;
	_event = NULL;
}

AGUIElement::AGUIElement(IGraphManager * graph, IEventManager * event, const Rect & rect)
{
	_graph = graph;
	_event = event;
	_rect = rect;
}

AGUIElement::~AGUIElement()
{
}

void AGUIElement::setGraph(IGraphManager * graph)
{
	_graph = graph;
}

void AGUIElement::setEvent(IEventManager * event)
{
	_event = event;
}

void AGUIElement::setPos(const Rect & rect)
{
	_rect = rect;
}

Rect	AGUIElement::getPos() const
{
	return (_rect);
}

void AGUIElement::setBackgroundColor(const Color & color)
{
	_backgroundColor = color;
}

void AGUIElement::setBackgroundOverColor(const Color & color)
{
	_backgroundOverColor = color;
}

void AGUIElement::setBackgroundSprite(const std::string & path)
{
	_backgroundSprite = path;
}

void AGUIElement::setBackgroundOverSprite(const std::string & path)
{
	_backgroundOverSprite = path;
}

void AGUIElement::setTransparentColor(const Color & color)
{
	_transparentColor = color;
}
