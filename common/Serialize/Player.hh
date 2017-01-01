#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
private:
  int			_missileCooldown;
  int			_idPlayer;
  int			_nbWave;
  int			_score;

public:
  Player(const int, const int, const int, const std::string &);
  virtual ~Player();

  int getWaveNumber() const;

  void setWaveNumber(const int nbWave);

  int getScore() const;

  virtual void		update();

  void setScore(const int score);

  int			getMissileCooldown() const;
  void			setMissileCooldown(const int);
  int			getIdPlayer() const;
};
