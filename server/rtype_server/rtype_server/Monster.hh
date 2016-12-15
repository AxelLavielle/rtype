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

  virtual void		setName(const std::string &);
  virtual std::string	getName() const;
  virtual void		update();
  void		setId(const int);
  int		getId() const;
};
