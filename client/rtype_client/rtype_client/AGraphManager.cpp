#include "AGraphManager.hh"



AGraphManager::AGraphManager()
{
	_winX = 1080;
	_winY = 720;
}


AGraphManager::~AGraphManager()
{
}

void AGraphManager::setWinHeight(const int & height)
{
	_winY = height;
}

void AGraphManager::setWinWidth(const int & width)
{
	_winX = width;
}
