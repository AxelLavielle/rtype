#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AGraphManager.hh"
#include "Rect.hh"

class SFML :
	public AGraphManager
{
public:
	SFML();
	virtual ~SFML();
	virtual bool init();
	virtual bool isWindowOpen();
	virtual void refresh();
	sf::RenderWindow *getWindow(void) const;
	virtual void close();
	bool drawRectangle(const std::string & spritePath, const Rect & rect);
	virtual bool setBackground(const std::string &imagePath);
private:
	sf::RenderWindow					*_window;
	std::vector<sf::Sprite>				_img;
	std::vector<sf::Texture>			_texture;
	//std::vector<sf::Drawable*>			_elem;
};

