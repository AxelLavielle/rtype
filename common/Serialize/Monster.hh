#pragma once

#include "AEntity.hh"

class Monster :
  public AEntity
{
protected:
  int			_id;
  std::string		_name;
public:
  Monster();
  virtual ~Monster();
  virtual void		update();
  IEntity	*createEntity();
  void		setId(const int);
  int		getId() const;
};
