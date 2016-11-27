#pragma once
#include "IEventManager.hpp"
class AEventManager :
	public IEventManager
{
public:
	AEventManager();
	virtual ~AEventManager();
	virtual bool refresh() = 0;
	virtual void setGraphManager(IGraphManager *graph) = 0;
	virtual std::string getKeyStroke() const = 0;
	virtual bool getCloseEvent() const = 0;
	virtual std::pair<int, int> getMousePOs() const = 0;
};

