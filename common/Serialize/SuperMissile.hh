#pragma once

#include "AEntity.hh"

class SuperMissile :
	public AEntity
{
public:
	SuperMissile(const int x, const int y, const int idPlayer);
	virtual ~SuperMissile();
	void update();
	int getIdPlayer() const;

private:
	int			_idPlayer;

};

