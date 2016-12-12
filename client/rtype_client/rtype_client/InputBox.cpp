#include "InputBox.hh"

InputBox::InputBox(IGraphManager *graph, IEventManager *event, const Rect &rect) : AGUIElement(graph, event, rect)
{
}

InputBox::~InputBox()
{
}

InputBox::InputBox() : AGUIElement()
{
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
	_graph->drawRectangle(Color(255, 255, 255), _rect);
	_graph->drawText(_key, _rect.getX(), _rect.getY(), 20, Color(0, 0, 0), "../../res/fonts/OpenSans-Regular.ttf");
	return (true);
}

bool InputBox::click()
{
	//Not implemented
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
