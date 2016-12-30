#pragma once

#include "AEntity.hh"

class Monster : public AEntity
{
public:
	Monster();
	Monster(const int, const int);
	virtual ~Monster();

	virtual void	update();
};
