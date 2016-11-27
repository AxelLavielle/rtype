#pragma once

#include <string>
#include "AGraphManager.hh"

class IEventManager
{
public:
	virtual ~IEventManager() {}
	virtual bool refresh() = 0;
	virtual void setGraphManager(IGraphManager *graph) = 0;
	virtual std::string getKeyStroke() const = 0;
	virtual bool getCloseEvent() const = 0;
	virtual std::pair<int, int> getMousePos() const = 0;
	virtual std::pair<int, int> getClickMousePos() const = 0;
};