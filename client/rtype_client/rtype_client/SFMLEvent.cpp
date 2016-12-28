#include "SFMLEvent.hh"

SFMLEvent::SFMLEvent()
{
	_keys.insert(std::make_pair(sf::Keyboard::Up, "UP"));
	_keys.insert(std::make_pair(sf::Keyboard::Down, "DOWN"));
	_keys.insert(std::make_pair(sf::Keyboard::Right, "RIGHT"));
	_keys.insert(std::make_pair(sf::Keyboard::Left, "LEFT"));
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
		case sf::Keyboard::Space:
			return ("SPACE");
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

std::string SFMLEvent::getKeyReleased() const
{
	if (_event.type == sf::Event::KeyReleased)
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
		case sf::Keyboard::Space:
			return ("SPACE");
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
	std::map<sf::Keyboard::Key, std::string>::iterator	it;

	if (key == "ML")
	{
		return (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left));
	}
	it = _keys.begin();
	while (it != _keys.end())
	{
		if (it->second == key)
			return (sf::Keyboard::isKeyPressed(it->first));
		++it;
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
