#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
private:
  int			_id;

public:
  Player(const int, const int);
  Player(const std::string &);
  virtual ~Player();

  virtual void		update();

  int			getId() const;
  void			setId(const int);
};
