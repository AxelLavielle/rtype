#include "Map.hh"

Map::Map()
{
}

Map::~Map()
{
}

std::vector<IEntity *>		Map::getEntityList() const
{
	return (_entityList);
}

void						Map::setEntityList(const std::vector<IEntity *> &entityList)
{
	_entityList = entityList;
}