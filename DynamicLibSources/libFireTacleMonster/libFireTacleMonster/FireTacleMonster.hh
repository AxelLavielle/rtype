#pragma once

#include "AEntity.hh"

class FireTacleMonster : public AEntity
{
private:
  int		_currentSprite;
public:
	FireTacleMonster();
	FireTacleMonster(const int, const int);
	virtual ~FireTacleMonster();

	virtual void	update();
};
