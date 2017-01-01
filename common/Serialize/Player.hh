#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
private:
  int			_missileCooldown;
  int			_idPlayer;
  int			_nbSuperShoot;

public:
  Player(const int, const int, const int, const std::string &);
  virtual ~Player();

  virtual void		update();

  int			getNbSuperShoot() const;
  void			setNbSuperShoot(const int shoot);
  int			getMissileCooldown() const;
  void			setMissileCooldown(const int);
  int			getIdPlayer() const;
};
