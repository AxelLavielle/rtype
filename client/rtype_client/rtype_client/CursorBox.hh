#pragma once

#include "AGUIElement.hh"

class CursorBox :
	public AGUIElement
{
public:
	CursorBox(IGraphManager *graph, IEventManager * event, const Rect & rect);
	CursorBox();
	virtual ~CursorBox();
	virtual bool draw();
	virtual bool click();
	virtual bool over();
	int getValue() const;
	void setValue(const int);

private:
	Rect		_rectLine;
	Rect		_rectBox;
	bool		_status;
};

