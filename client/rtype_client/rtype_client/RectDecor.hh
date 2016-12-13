#pragma once
#include "AGUIElement.hh"
class RectDecor :
	public AGUIElement
{
public:
	RectDecor(IGraphManager * graph, IEventManager * event, const Rect & rect);
	RectDecor();
	virtual ~RectDecor();
	virtual bool click();
	virtual bool over();
	virtual bool draw();
};

