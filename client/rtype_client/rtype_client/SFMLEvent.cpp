#include "SFMLEvent.hh"

SFMLEvent::SFMLEvent()
{
}


SFMLEvent::~SFMLEvent()
{
}

bool SFMLEvent::refresh()
{
	if (_graph)
		return (_graph->getWindow()->pollEvent(_event));
	return (false);
}

void SFMLEvent::setGraphManager(IGraphManager * graph)
{
	_graph = static_cast<SFML*>(graph);
}

std::string SFMLEvent::getTextEntered()
{
	if (_event.type == sf::Event::TextEntered)
	{
		std::string res = "";
		res += static_cast<char>(_event.text.unicode);
		return (res);
	}
	return ("");
}

std::string SFMLEvent::getKeyStroke() const
{
	if (_event.type == sf::Event::KeyPressed)
	{
		switch (_event.key.code)
		{
		case sf::Keyboard::Escape:
			return ("ECHAP");
		case sf::Keyboard::Up:
			return ("UP");
		case sf::Keyboard::Left:
			return ("LEFT");
		case sf::Keyboard::Down:
			return ("DOWN");
		case sf::Keyboard::Right:
			return ("RIGHT");
		default:
		  break;
		}
	}
	else if (_event.type == sf::Event::MouseButtonPressed)
	{
		switch (_event.mouseButton.button)
		{
		case sf::Mouse::Right:
		  return ("MR");
		case sf::Mouse::Left:
		  return ("ML");
		default:
		  break;
		}
	}
	return ("");
}

bool SFMLEvent::isPressed(const std::string & key)
{
	if (key == "ML")
	{
		return (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
	}
	return (false);
}

bool SFMLEvent::getCloseEvent() const
{
	if (_event.type == sf::Event::Closed)
		return (true);
	return (false);
}

std::pair<int, int> SFMLEvent::getMousePos() const
{
	std::pair<int, int> pos(-1, -1);

	if (_event.type == sf::Event::MouseMoved)
	{
		pos.first = _event.mouseMove.x;
		pos.second = _event.mouseMove.y;
	}
	return (pos);
}

std::pair<int, int> SFMLEvent::getClickMousePos() const
{
	std::pair<int, int>		res(-1, -1);

	if (_event.type == sf::Event::MouseButtonPressed)
	{
		if (_event.mouseButton.button == sf::Mouse::Left)
		{
			res.first = _event.mouseButton.x;
			res.second = _event.mouseButton.y;
		}
	}
	return (res);
}
