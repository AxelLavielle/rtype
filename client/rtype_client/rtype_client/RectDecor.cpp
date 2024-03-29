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
	return (false);
}

bool RectDecor::over()
{
	return (false);
}

bool RectDecor::draw()
{
	if (_transparentColor.getR() == -1)
	{
		if (_backgroundColor.getR() == -1)
			_graph->drawRectangle(_backgroundSprite, _rect);
		else
			_graph->drawRectangle(_backgroundColor, _rect);
	}
	else
		_graph->drawRectangle(_backgroundSprite, _rect, _transparentColor);
	return (true);
}
