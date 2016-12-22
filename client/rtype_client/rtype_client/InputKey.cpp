#include "InputKey.hh"

InputKey::InputKey(IGraphManager *graph, IEventManager *event, const Rect &rect) : AGUIElement(graph, event, rect)
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
	_typeName = "InputKey";
	_focus = false;
}

InputKey::~InputKey()
{
}

InputKey::InputKey() : AGUIElement()
{
	_backgroundColor.setR(255);
	_backgroundColor.setG(255);
	_backgroundColor.setB(255);
}

void	InputKey::setText(const std::string &text)
{
	_key = text;
}

std::string InputKey::getText() const
{
	return (_key);
}

bool InputKey::getInput()
{
	std::string key;

	if (_focus)
	  {
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
	    _key = key;
	    return (true);
	  }
	return (false);
}

void InputKey::setTextColor(const Color & color)
{
	_textColor = color;
}

bool InputKey::draw()
{
	_graph->drawRectangle(_backgroundSprite, _rect);
	_graph->drawText(_key, _rect.getX() + 10, _rect.getY(), 20, _textColor, _fontPath);
	return (true);
}

bool InputKey::click()
{
  std::pair<int, int>		pos;
  std::string				tmp;

  pos = _event->getClickMousePos();
  getInput();
  if (pos.first != -1 && pos.second != -1
      && pos.first > _rect.getX() && pos.first < _rect.getX() + _rect.getWidth()
      && pos.second > _rect.getY() && pos.second < _rect.getY() + _rect.getHeight())
    {
      _focus = true;
	  // tmp = _backgroundSprite;
	  // _backgroundSprite = _backgroundOverSprite;
	  // _backgroundOverSprite = tmp;
      _backgroundColor.setR(192);
      _backgroundColor.setG(192);
      _backgroundColor.setB(192);
      return (true);
    }
  else if (pos.first != -1 && pos.second != -1)
    {
      _focus = false;
	  // tmp = _backgroundOverSprite;
	  // _backgroundOverSprite = _backgroundSprite;
	  // _backgroundSprite = tmp;
      _backgroundColor.setR(255);
      _backgroundColor.setG(255);
      _backgroundColor.setB(255);
    }
  return (false);
}

bool InputKey::over()
{
	//Not implemented
	return (false);
}

void InputKey::setGraph(IGraphManager * graph)
{
	_graph = graph;
}

void InputKey::setEvent(IEventManager * event)
{
	_event = event;
}
