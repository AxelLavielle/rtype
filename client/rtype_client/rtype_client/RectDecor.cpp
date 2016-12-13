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
	if (_transparantColor.getR() == -1)
	{
		if (_backgroundColor.getR() == -1)
			_graph->drawRectangle(_backgroundSprite, _rect);
		else
			_graph->drawRectangle(_backgroundColor, _rect);
	}
	else
		_graph->drawRectangle(_backgroundSprite, _rect, _transparantColor);
	return (true);
}
