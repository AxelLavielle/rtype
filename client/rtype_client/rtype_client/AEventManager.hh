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
	virtual std::pair<int, int> getMousePos() const = 0;
	virtual std::pair<int, int> getClickMousePos() const = 0;
	virtual std::string getTextEntered() = 0;
	virtual bool isPressed(const std::string & key) = 0;
};

