#pragma once

#include "AEntity.hh"

class BossMonster : public AEntity
{
private:
	int		_currentSprite;
public:
	BossMonster();
	BossMonster(const int, const int);
	virtual ~BossMonster();

	virtual void	update();
};
