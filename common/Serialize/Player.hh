#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
protected:
  int			_id;
public:
  Player();
  virtual ~Player();
  virtual void		update();
  int			getId() const;
  void			setId(const int);
};
