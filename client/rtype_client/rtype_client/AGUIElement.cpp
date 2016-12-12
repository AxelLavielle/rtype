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
