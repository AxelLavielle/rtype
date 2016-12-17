#pragma once

#include "IMenu.hpp"
#include "IGraphManager.hpp"
#include "IEventManager.hpp"
#include "Serialize.hh"

class AMenu :
	public IMenu
{
public:
	AMenu();
	virtual ~AMenu();
	virtual void setGraphManager(IGraphManager * graph);
	virtual void setEventManager(IEventManager * event);
	virtual bool launch() = 0;
	virtual void setSocketTCPSocket(ASocketClient * socket);
protected:
	IGraphManager		*_graph;
	IEventManager		*_event;
	ASocketClient		*_socket;
};

