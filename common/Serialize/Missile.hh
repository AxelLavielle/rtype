#pragma once

#include "AEntity.hh"

class Missile : public AEntity
{
private:
	int			_idPlayer;

public:
	Missile(const int, const int, const int);
	virtual	~Missile();

	virtual void	update();
	int				getIdPlayer() const;
};

