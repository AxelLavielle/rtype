#pragma once

#include <string>
#include "IEntity.hpp"

class AEntity :
	public IEntity
{
public:
	AEntity();
	virtual ~AEntity();
	virtual		void			update();
	virtual		double			getPosX() const;
	virtual		void			setPosX(const double);
	virtual		double			getPosY() const;
	virtual		void			setPosY(const double);
	virtual		rtype::EntityType	getType(void) const;
	virtual		void			setType(const rtype::EntityType &);
	virtual		IEntity			*entityCreator();
protected:
  double					_posX;
  double					_posY;
  std::string					_spritePath;
  rtype::EntityType		       		_type;
};
