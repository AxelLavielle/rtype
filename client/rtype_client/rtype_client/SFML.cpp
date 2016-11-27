#include "SFML.hh"



SFML::SFML()
{
}


SFML::~SFML()
{
	delete _window;
}

bool SFML::init()
{
	_window = new sf::RenderWindow();
	_window->create(sf::VideoMode(_winX, _winY), "RType");
	return (true);
}

bool SFML::isWindowOpen()
{
	return (_window->isOpen());
}

void SFML::refresh()
{
	std::vector<sf::Sprite>::iterator	it;
	_window->clear();
	it = _img.begin();
	while (it != _img.end())
	{
		_window->draw(*it);
		++it;
	}
	_window->display();
}

sf::RenderWindow *SFML::getWindow(void) const
{
	return (_window);
}

void SFML::close()
{
	_window->close();
}

bool SFML::drawRectangle(const std::string & spritePath, const Rect &rect)
{
	sf::Texture		img;
	sf::Sprite		sprite;

	if (!img.loadFromFile(spritePath))
		return (false);
	_texture.push_back(img);
	sprite.setTexture(_texture.back());
	_img.push_back(sprite);
	return (true);
}

bool SFML::setBackground(const std::string & imagePath)
{
	sf::Texture		img;
	sf::Sprite		sprite;

	if (!img.loadFromFile(imagePath))
		return (false);
	_texture.push_back(img);
	sprite.setTexture(_texture.back());
	sprite.scale(0.6f, 0.7f);
	_img.push_back(sprite);
	return (true);
}
