#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "AGraphManager.hh"

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
	virtual bool setBackground(const std::string &imagePath);
private:
	sf::RenderWindow					*_window;
	std::vector<sf::Sprite>				_img;
	std::vector<sf::Texture>			_texture;
	//std::vector<sf::Drawable*>			_elem;
};

