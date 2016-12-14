#include "SFML.hh"

SFML::SFML()
{
}


SFML::~SFML()
{
	std::vector<std::pair<sf::Texture*, std::string>>::iterator			it;
	std::vector<std::pair<sf::Font*, std::string>>::iterator			it2;
	std::vector<std::pair<sf::Image*, std::string>>::iterator			it3;

	it = _texture.begin();
	while (it != _texture.end())
	{
		delete (*it).first;
		++it;
	}
	it2 = _fonts.begin();
	while (it2 != _fonts.end())
	{
		delete (*it2).first;
		++it2;
	}
	it3 = _img.begin();
	while (it3 != _img.end())
	{
		delete (*it3).first;
		++it3;
	}
	delete _window;
}

void SFML::setMouseCursorVisible(const bool flag)
{
	_window->setMouseCursorVisible(flag);
}

std::pair<int, int>	SFML::getScreenSize() const
{
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	return (std::pair<int, int>(desktop.width, desktop.height));
}

std::pair<int, int> SFML::getWindowSize() const
{
	sf::Vector2u		vector;

	vector = _window->getSize();
	return (std::pair<int, int>(vector.x, vector.y));
}

bool SFML::init()
{
	_window = new sf::RenderWindow();
	_window->create(sf::VideoMode(_winX, _winY), "RTYPE");
	return (true);
}

bool SFML::setFullScreen(const bool mode)
{
	if (mode)
	{
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		_window->create(sf::VideoMode(desktop.width, desktop.height), "RTYPE", sf::Style::Fullscreen);
	}
	return (true);
}

bool SFML::isWindowOpen()
{
	return (_window->isOpen());
}

void SFML::clearWindow()
{
	_window->clear();
}

void SFML::refresh()
{
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

sf::Font *SFML::getFont(const std::string & path) const
{
	std::vector<std::pair<sf::Font*, std::string>>::const_iterator it;

	it = _fonts.begin();
	while (it != _fonts.end())
	{
		if ((*it).second == path)
			return ((*it).first);
		++it;
	}
	return (NULL);
}

bool SFML::drawText(const std::string & text, const int & posX, const int & posY, const int &size, const Color &color, const std::string & fontPath)
{
	sf::Font	*font;
	sf::Text	txt;

	if (!(font = getFont(fontPath)))
	{
		font = new sf::Font();
		if (!font->loadFromFile(fontPath))
			return (false);
		_fonts.push_back(std::pair<sf::Font*, std::string>(font, fontPath));
	}
	txt.setFont(*font);
	txt.setString(text);
	txt.setCharacterSize(size);
	txt.setFillColor(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));	
	txt.setPosition(posX, posY);
	_window->draw(txt);
	return (true);
}

bool SFML::drawRectangle(const std::string & spritePath, const Rect &rect, const Color & transparentColor)
{
	sf::Image			*image;
	sf::Texture			*texture;
	sf::RectangleShape	rec(sf::Vector2f(rect.getWidth(), rect.getHeight()));

	if (!(image = getImage(spritePath)))
	{
		image = new sf::Image();
		if (!image->loadFromFile(spritePath))
			return (false);
		texture = new sf::Texture();
		image->createMaskFromColor(sf::Color(transparentColor.getR(), transparentColor.getG(), transparentColor.getB(), transparentColor.getA()));
		_img.push_back(std::pair<sf::Image*, std::string>(image, spritePath));
		_texture.push_back(std::pair<sf::Texture*, std::string>(texture, spritePath));
	}
	else
	{
		texture = getTexture(spritePath);
	}
	texture->loadFromImage(*image);
	rec.setTexture(texture);
	rec.setPosition(rect.getX(), rect.getY());
	_window->draw(rec);
	return (true);
}

bool SFML::drawRectangle(const std::string & spritePath, const Rect &rect)
{
	sf::Texture			*img;
	sf::RectangleShape	rec(sf::Vector2f(rect.getWidth(), rect.getHeight()));

	if (!(img = getTexture(spritePath)))
	{
		img = new sf::Texture();
		if (!img->loadFromFile(spritePath))
			return (false);
		_texture.push_back(std::pair<sf::Texture*, std::string>(img, spritePath));
	}
	rec.setTexture(img);
	rec.setPosition(rect.getX(), rect.getY());
	_window->draw(rec);
	return (true);
}

bool SFML::drawRectangle(const Color & color, const Rect & rect)
{
	sf::RectangleShape	rec(sf::Vector2f(rect.getWidth(), rect.getHeight()));

	rec.setFillColor(sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
	rec.setPosition(rect.getX(), rect.getY());
	_window->draw(rec);
	return (true);
}

sf::Texture *SFML::getTexture(const std::string &path) const
{
	std::vector<std::pair<sf::Texture*, std::string>>::const_iterator it;

	it = _texture.begin();
	while (it != _texture.end())
	{
		if ((*it).second == path)
			return ((*it).first);
		++it;
	}
	return (NULL);
}

sf::Image *SFML::getImage(const std::string &path) const
{
	std::vector<std::pair<sf::Image*, std::string>>::const_iterator it;

	it = _img.begin();
	while (it != _img.end())
	{
		if ((*it).second == path)
			return ((*it).first);
		++it;
	}
	return (NULL);
}

bool SFML::setBackground(const std::string & imagePath, const float scaleX, const float scaleY)
{
	sf::Texture		*img;
	sf::Sprite		sprite;

	if (!(img = getTexture(imagePath)))
	{
		img = new sf::Texture();
		if (!img->loadFromFile(imagePath))
			return (false);
		_texture.push_back(std::pair<sf::Texture*, std::string>(img, imagePath));
	}
	sprite.setTexture(*img);
	if (scaleX != -1)
		sprite.scale(scaleX, scaleY);
	_window->draw(sprite);
	return (true);
}
