#pragma once
#include "AGUIElement.hh"
class CheckBox :
	public AGUIElement
{
public:
	CheckBox(IGraphManager * graph, IEventManager * event, const Rect & rect);
	CheckBox();
	virtual ~CheckBox();
	virtual bool draw();
	virtual bool click();
	virtual bool over();
	bool isChecked() const;
private:
	bool		_status;
};

