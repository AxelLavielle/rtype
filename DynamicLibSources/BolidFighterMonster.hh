#pragma once

#include "AEntity.hh"

class BolidFighterMonster : public AEntity
{
private:
	int		_currentSprite;
public:
	BolidFighterMonster();
	BolidFighterMonster(const int, const int);
	virtual ~BolidFighterMonster();

	virtual void	update();
};
