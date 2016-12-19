#pragma once

#include "IGraphManager.hpp"
#include "IEventManager.hpp"
#include "SocketClientTCP.hh"
#include "AMutex.hh"

class IMenu
{
public:
	virtual ~IMenu() {}
	virtual bool init() = 0;
	virtual void setGraphManager(IGraphManager * graph) = 0;
	virtual void setEventManager(IEventManager * event) = 0;
	virtual void setSocketTCPSocket(ASocketClient * socket) = 0;
	virtual bool launch() = 0;
	virtual void setMutex(AMutex * mutex) = 0;
};