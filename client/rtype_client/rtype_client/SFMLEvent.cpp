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

std::string SFMLEvent::getKeyStroke() const
{
	if (_event.type == sf::Event::KeyPressed)
	{
		switch (_event.key.code)
		{
		case sf::Keyboard::Escape:
			return ("ECHAP");
		}
	}
	return ("");
}

bool SFMLEvent::getCloseEvent() const
{
	if (_event.type == sf::Event::Closed)
		return (true);
	return (false);
}

std::pair<int, int> SFMLEvent::getMousePOs() const
{
	std::pair<int, int> pos(-1, -1);

	if (_event.type == sf::Event::MouseMoved)
	{
		pos.first = _event.mouseMove.x;
		pos.second = _event.mouseMove.y;
	}
	return (pos);
}

