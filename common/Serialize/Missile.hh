#pragma once

#include "AEntity.hh"

class Missile : public AEntity
{
public:
	Missile(const int, const int);
	virtual	~Missile();

	virtual void	update();
};

