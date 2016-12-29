#pragma once

#include "AEntity.hh"

class Monster :
  public AEntity
{
private:
  int		_id;
public:
	Monster();
	Monster(const int, const int);
	virtual ~Monster();

	virtual void	update();

	void		setId(const int);
	int		getId() const;
};
