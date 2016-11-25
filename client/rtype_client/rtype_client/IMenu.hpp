#pragma once

#include "IGraphManager.hpp"
#include "IEventManager.hpp"

class IMenu
{
public:
	virtual ~IMenu() {}
	virtual bool init() = 0;
	virtual void setGraphManager(IGraphManager * graph) = 0;
	virtual void setEventManager(IEventManager * event) = 0;
	virtual bool launch() = 0;
};