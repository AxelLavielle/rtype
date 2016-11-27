#include "Button.hh"

Button::Button(IGraphManager *graph, IEventManager *event, const Rect &rect, const std::string &txt)
{
	_graph = graph;
	_event = event;
	_rect = rect;
	_txt = txt;
}

Button::~Button()
{
}

bool Button::draw()
{
	if (!_over)
	{
		_graph->drawRectangle("../../res/img/button.jpg", _rect);
		_graph->drawText("PLAY", _rect.getX() + _posXText, _rect.getY() + _posYText, _textSize, Color(224, 224, 224, 255), "../../res/fonts/Aerospace.ttf");
	}
	else
	{
		_graph->drawRectangle("../../res/img/button.jpg", _rect);
		_graph->drawText("PLAY", _rect.getX() + _posXText, _rect.getY() + _posYText, _textSize, Color(224, 224, 224, 255), "../../res/fonts/Aerospace.ttf");
	}
	return (true);
}

bool Button::over()
{
	std::pair<int, int>		pos;

	pos = _event->getMousePos();
	if (pos.first != -1 && pos.second != -1
			&& pos.first > _rect.getX() && pos.first < _rect.getX() + _rect.getWidth()
			&& pos.second > _rect.getY() && pos.second < _rect.getY() + _rect.getHeight())
	{
		_over = true;
		return (true);
	}
	_over = false;
	return (false);
}

bool Button::click()
{
	std::pair<int, int>		pos;

	pos = _event->getClickMousePos();
	if (pos.first != -1 && pos.second != -1
			&& pos.first > _rect.getX() && pos.first < _rect.getX() + _rect.getWidth()
			&& pos.second > _rect.getY() && pos.second < _rect.getY() + _rect.getHeight())
		return (true);
	return (false);
}

void Button::setTextPos(const int & x, const int & y)
{
	_posXText = x;
	_posYText = y;
}

void Button::setTextSize(const int & size)
{
	_textSize = size;
}
