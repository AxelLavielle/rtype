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
	void setCheckedSprite(const std::string & sprite);
	bool isChecked() const;
private:
	bool			_status;
	std::string		_checkedSprite;
};

