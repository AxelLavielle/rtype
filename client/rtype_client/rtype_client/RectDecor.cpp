#include "RectDecor.hh"



RectDecor::RectDecor(IGraphManager * graph, IEventManager * event, const Rect & rect) : AGUIElement(graph, event, rect)
{
}

RectDecor::RectDecor() : AGUIElement()
{
}


RectDecor::~RectDecor()
{
}

bool RectDecor::click()
{
	//Not implemented
	return (false);
}

bool RectDecor::over()
{
	//Not implemented
	return (false);
}

bool RectDecor::draw()
{
	_graph->drawRectangle(_backgroundSprite, _rect);
	return (true);
}
