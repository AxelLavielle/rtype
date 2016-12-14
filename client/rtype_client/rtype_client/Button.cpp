#include "Button.hh"

Button::Button(IGraphManager *graph, IEventManager *event, const Rect &rect, const std::string &txt) : AGUIElement(graph, event, rect)
{
	_txt = txt;
	_backgroundSprite = "../../res/img/button.jpg";
	_backgroundOverSprite = "../../res/img/button_over.jpg";
}

Button::Button() : AGUIElement()
{
}

Button::~Button()
{
}

bool Button::draw()
{
	if (!_over)
	{
		if (_backgroundColor.getR() == -1)
			_graph->drawRectangle(_backgroundSprite, _rect);
		else
			_graph->drawRectangle(_backgroundColor, _rect);
		_graph->drawText(_txt, _rect.getX() + _posXText, _rect.getY() + _posYText, _textSize, Color(135, 206, 250, 255), "../../res/fonts/Aerospace.ttf");
	}
	else
	{
		if (_backgroundOverColor.getR() == -1)
			_graph->drawRectangle(_backgroundOverSprite, _rect);
		else
			_graph->drawRectangle(_backgroundOverColor, _rect);
		_graph->drawText(_txt, _rect.getX() + _posXText, _rect.getY() + _posYText, _textSize, Color(135, 206, 250, 255), "../../res/fonts/Aerospace.ttf");
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

void Button::setTextPos(const int x, const int y)
{
	_posXText = x;
	_posYText = y;
}

void Button::setTextSize(const int size)
{
	_textSize = size;
}

void Button::setText(const std::string & txt)
{
	_txt = txt;
}
