#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
private:
  int			_missileCooldown;

public:
  Player(const int, const int);
  Player(const std::string &);
  virtual ~Player();

  virtual void		update();

  int			getMissileCooldown() const;
  void			setMissileCooldown(const int);
};
