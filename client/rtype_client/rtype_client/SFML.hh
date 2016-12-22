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
	virtual void setMouseCursorVisible(const bool flag);
	virtual std::pair<int, int> getScreenSize() const;
	virtual std::pair<int, int> getWindowSize() const;
	virtual bool init();
	virtual bool setFullScreen(const bool mode);
	virtual bool isWindowOpen();
	virtual void clearWindow();
	virtual void refresh();
	sf::RenderWindow *getWindow(void) const;
	virtual void close();
	virtual bool drawText(const std::string & text, const int & posX, const int & posY, const int &size, const Color &color, const std::string & font = "../../res/font/Aerospace.ttf");
	virtual bool drawRectangle(const std::string & spritePath, const Rect & rect, const Color & transparentColor);
	virtual bool drawRectangle(const std::string & spritePath, const Rect & rect, const Rect & rect2);
	virtual bool drawRectangle(const std::string & spritePath, const Rect & rect);
	virtual bool drawRectangle(const Color & color, const Rect & rect);
	virtual bool setBackground(const std::string &imagePath, const float scaleX, const float scaleY);
private:
	sf::RenderWindow											*_window;
	std::vector<std::pair<sf::Texture*, std::string> >			_texture;
	std::vector<std::pair<sf::Image*, std::string> >			_img;
	std::vector<std::pair<sf::Font*, std::string> >				_fonts;
	//std::vector<sf::Drawable*>			_elem;

	sf::Texture * getTexture(const std::string & path) const;
	sf::Image * getImage(const std::string & path) const;
	sf::Font * getFont(const std::string &path) const;
};

