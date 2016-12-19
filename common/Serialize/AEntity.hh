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
	virtual		rtype::EntityType	getType() const;
	virtual		void			setType(const rtype::EntityType &);
	virtual		void			setName(const std::string &);
	virtual		std::string		getName() const;
	virtual		void			setSpriteRepo(const std::string &);
	virtual		std::string		getSpriteRepo() const;
  	virtual		double			getSpeedX() const;
	virtual		void			setSpeedX(const double);
  	virtual		double			getSpeedY() const;
	virtual		void			setSpeedY(const double);
  	virtual		int			getLife() const;
	virtual		void			setLife(const int);
protected:
  double					_posX;
  double					_speedY;
 double						_speedX;
  double					_posY;
  int						_life;
  std::string					_spritePath;
  rtype::EntityType		       		_type;
  std::string					_name;
};
