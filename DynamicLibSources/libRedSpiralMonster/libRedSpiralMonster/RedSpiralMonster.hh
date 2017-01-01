#pragma once

#include "AEntity.hh"

class RedSpiralMonster : public AEntity
{
private:
	int		_currentSprite;
public:
	RedSpiralMonster();
	RedSpiralMonster(const int, const int);
	virtual ~RedSpiralMonster();

	virtual void	update();
};
