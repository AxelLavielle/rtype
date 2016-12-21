#pragma once

#include "IMenu.hpp"
#include "IGraphManager.hpp"
#include "IEventManager.hpp"
#include "Serialize.hh"
#include "AMutex.hh"
#include "ThreadPool.hh"

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
	virtual void setMutex(AMutex * mutex);
	virtual bool init() = 0;
	virtual void setIp(const std::string &ip) = 0;
	virtual void setPort(const int port) = 0;

protected:
	IGraphManager		*_graph;
	IEventManager		*_event;
	ASocketClient		*_socket;
	AMutex				*_mutex;
	ThreadPool			_pool;
};
