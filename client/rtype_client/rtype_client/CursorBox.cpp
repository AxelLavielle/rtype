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
	_graph->drawRectangle(_backgroundColor, _rectLine);
	_graph->drawRectangle(_backgroundColor, _rectBox);
	return (true);
}

bool CursorBox::click()
{
	std::pair<int, int>		pos;
	std::string				key;

	pos = _event->getClickMousePos();
	if (pos.first != -1 && pos.second != -1
		&& pos.first > _rectLine.getX() && pos.first < _rectLine.getX() + _rectLine.getWidth()
		&& pos.second > _rectLine.getY() && pos.second < _rectLine.getY() + _rectLine.getHeight())
	{
		_rectBox.setX(pos.first - _rectBox.getWidth() / 2);
		return (true);
	}
	//key = _event->getKeyStroke();
	//while (key == "ML")
	//{
	//	key = _event->getKeyStroke();
	//	pos = _event->getClickMousePos();
	//	std::cout << "click2" << std::endl;
	//	_rectBox.setX(pos.first - _rectBox.getWidth() / 2);
	//	return (true);
	//}
	return (false);
}

bool CursorBox::over()
{
	//Not implemented
	return (false);
}
