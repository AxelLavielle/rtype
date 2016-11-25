#include "AMenu.hh"



AMenu::AMenu()
{
}


AMenu::~AMenu()
{
}

void AMenu::setGraphManager(IGraphManager * graph)
{
	_graph = graph;
}

void AMenu::setEventManager(IEventManager * event)
{
	_event = event;
}
