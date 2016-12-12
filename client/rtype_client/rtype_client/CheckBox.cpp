#include "CheckBox.hh"



CheckBox::CheckBox(IGraphManager * graph, IEventManager * event, const Rect & rect) : AGUIElement(graph, event, rect)
{
}

CheckBox::CheckBox() : AGUIElement()
{
	_status = false;
}


CheckBox::~CheckBox()
{
}

bool CheckBox::draw()
{
	//Not implemented
	return (true);
}

bool CheckBox::click()
{
	//Not implemented
	return (false);
}

bool CheckBox::over()
{
	//Not implemented
	return (false);
}

bool CheckBox::isChecked() const
{
	return (_status);
}
