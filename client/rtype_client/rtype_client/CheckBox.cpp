#include "CheckBox.hh"


CheckBox::CheckBox(IGraphManager * graph, IEventManager * event, const Rect & rect) : AGUIElement(graph, event, rect)
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
	_status = false;
}

CheckBox::CheckBox() : AGUIElement()
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
	_status = false;
}

CheckBox::~CheckBox()
{
}

void	CheckBox::setCheckedSprite(const std::string & sprite)
{
	_checkedSprite = sprite;
}

bool CheckBox::draw()
{
	if (!_status)
		_graph->drawRectangle(_backgroundSprite, _rect);
	else
		_graph->drawRectangle(_checkedSprite, _rect);
	return (true);
}

bool CheckBox::click()
{
	std::pair<int, int>		pos;

	pos = _event->getClickMousePos();
	if (pos.first != -1 && pos.second != -1
		&& pos.first > _rect.getX() && pos.first < _rect.getX() + _rect.getWidth()
		&& pos.second > _rect.getY() && pos.second < _rect.getY() + _rect.getHeight())
	{

		_status = !_status;
		if (_status)
		{
			_backgroundColor.setR(192);
			_backgroundColor.setG(192);
			_backgroundColor.setB(192);
		}
		else
		{
			_backgroundColor.setR(255);
			_backgroundColor.setG(255);
			_backgroundColor.setB(255);
		}
		return (true);
	}
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
