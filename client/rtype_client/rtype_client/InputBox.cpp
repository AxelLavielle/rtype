#include "InputBox.hh"

InputBox::InputBox(IGraphManager *graph, IEventManager *event, const Rect &rect) : AGUIElement(graph, event, rect)
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
	_typeName = "InputBox";
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
	if (key == "" || _key.size() >= 32)
		return (false);
	_key += key;
	return (true);
}

void InputBox::setTextColor(const Color & color)
{
	_textColor = color;
}

bool InputBox::draw()
{
	_graph->drawRectangle(_backgroundSprite, _rect);
	_graph->drawText(_key, _rect.getX() + 10, _rect.getY(), 20, _textColor, "../../res/fonts/OpenSans-Regular.ttf");
	return (true);
}

bool InputBox::click()
{
	std::pair<int, int>		pos;

	pos = _event->getClickMousePos();
	getInput();
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
