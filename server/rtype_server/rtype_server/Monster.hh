#pragma once

#include "AEntity.hh"

class Monster :
  public AEntity
{
public:
  Monster();
  virtual ~Monster();
  virtual void		setId(const int);
  virtual int		getId(void) const;
  virtual void		setName(const std::string &);
  virtual std::string	getName(void) const;
  virtual void		update(void);
protected:
  int			_id;
  std::string		_name;
};
