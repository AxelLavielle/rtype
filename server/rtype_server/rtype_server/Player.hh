#pragma once

#include "AEntity.hh"

class Player :
	public AEntity
{
public:
  Player();
  virtual ~Player();
  virtual int		getId() const;
  virtual void		setId(const int);
  virtual void		update(void);
  IEntity	*entityCreator();
protected:
  int			_id;
};
