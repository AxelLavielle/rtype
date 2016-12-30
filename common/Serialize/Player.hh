#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
private:
  int			_missileCooldown;
  int			_idPlayer;

public:
  Player(const int, const int, const int);
  virtual ~Player();

  virtual void		update();

  int			getMissileCooldown() const;
  void			setMissileCooldown(const int);
  int			getIdPlayer() const;
};
