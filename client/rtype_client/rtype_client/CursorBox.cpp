#include "CursorBox.hh"



CursorBox::CursorBox(IGraphManager * graph, IEventManager * event, const Rect & rect) : AGUIElement(graph, event, rect)
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
	_rectLine = rect;
	_rectBox = rect;
	_rectLine.setHeight(rect.getHeight() - 20);
	_rectBox.setY(rect.getY() - rect.getHeight() / 3);
	_rectBox.setWidth(rect.getWidth() / 7);
	_status = false;
}

CursorBox::CursorBox() : AGUIElement()
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
}


CursorBox::~CursorBox()
{
}

bool CursorBox::draw()
{
	_graph->drawRectangle(_backgroundSprite, _rectLine);
	_graph->drawRectangle(_backgroundOverSprite, _rectBox);
	return (true);
}
#include <iostream>
bool CursorBox::click()
{
	std::pair<int, int>		pos;
	bool					key;

	pos = _event->getClickMousePos();
	if (pos.first != -1 && pos.second != -1
		&& pos.first > _rectBox.getX() && pos.first < _rectBox.getX() + _rectBox.getWidth()
		&& pos.second > _rectBox.getY() && pos.second < _rectBox.getY() + _rectBox.getHeight())
	{
		_status = true;
		//_rectBox.setX(pos.first - _rectBox.getWidth() / 2);
		return (true);
	}
	key = _event->isPressed("ML");
	pos = _event->getMousePos();
	if (key && _status)
	{
		if (pos.first - _rectBox.getWidth() / 2 < _rect.getX() + _rect.getWidth() - _rectBox.getWidth() && pos.first - _rectBox.getWidth() / 2 > _rect.getX())
			_rectBox.setX(pos.first - _rectBox.getWidth() / 2);
	}
	else
		_status = false;
	return (false);
}

int CursorBox::getValue() const
{
  return ((_rectBox.getX() - _rectBox.getWidth() / 2) - _rect.getX());
}

bool CursorBox::over()
{
	//Not implemented
	return (false);
}
