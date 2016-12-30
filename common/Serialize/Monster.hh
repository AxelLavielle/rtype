#pragma once

#include "AEntity.hh"

class Monster : public AEntity
{
private:
	int		_currentSprite;
public:
	Monster();
	Monster(const int, const int);
	virtual ~Monster();

	virtual void	update();
};
