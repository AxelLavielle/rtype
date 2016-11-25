#pragma once

#include <SFML/Graphics.hpp>
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
	virtual std::string getKeyStroke() const;
	virtual bool getCloseEvent() const;
private:
	SFML					*_graph;
	sf::Event				_event;
};

