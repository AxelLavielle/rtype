#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "AEventManager.hh"
#include "SFML.hh"

class SFMLEvent :
	public AEventManager
{
public:
	SFMLEvent();
	virtual ~SFMLEvent();
	virtual bool refresh();
	virtual void setGraphManager(IGraphManager *graph);
	virtual std::string getTextEntered();
	virtual std::string getKeyStroke() const;
	virtual std::string getKeyReleased() const;
	virtual bool isPressed(const std::string & key);
	virtual bool getCloseEvent() const;
	virtual std::pair<int, int> getMousePos() const;
	virtual std::pair<int, int> getClickMousePos() const;
private:
	SFML										*_graph;
	sf::Event									_event;
	std::map<sf::Keyboard::Key, std::string>	_keys;
};

