#include "InputBox.hh"

InputBox::InputBox(IGraphManager *graph, IEventManager *event, const Rect &rect) : AGUIElement(graph, event, rect)
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
}

InputBox::~InputBox()
{
}

InputBox::InputBox() : AGUIElement()
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
}

std::string InputBox::getText() const
{
	return (_key);
}

bool InputBox::getInput()
{
	std::string key;

	key = "";
	key = _event->getTextEntered();
	if (key[0] == 8)
	{
		if (_key.size() > 0)
			_key.pop_back();
		key = "";
	}
	if (key == "")
		return (false);
	_key += key;
	return (true);
}

bool InputBox::draw()
{
	_graph->drawRectangle(_backgroundColor, _rect);
	_graph->drawText(_key, _rect.getX(), _rect.getY(), 20, Color(0, 0, 0), "../../res/fonts/OpenSans-Regular.ttf");
	return (true);
}

bool InputBox::click()
{
	std::pair<int, int>		pos;

	pos = _event->getClickMousePos();
	if (pos.first != -1 && pos.second != -1
		&& pos.first > _rect.getX() && pos.first < _rect.getX() + _rect.getWidth()
		&& pos.second > _rect.getY() && pos.second < _rect.getY() + _rect.getHeight())
	{
		_backgroundColor.setR(192);
		_backgroundColor.setG(192);
		_backgroundColor.setB(192);
		return (true);
	}
	else if (pos.first != -1 && pos.second != -1)
	{
		_backgroundColor.setR(255);
		_backgroundColor.setG(255);
		_backgroundColor.setB(255);
	}
	return (false);
}

bool InputBox::over()
{
	//Not implemented
	return (false);
}

void InputBox::setGraph(IGraphManager * graph)
{
	_graph = graph;
}

void InputBox::setEvent(IEventManager * event)
{
	_event = event;
}
