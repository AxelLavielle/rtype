#pragma once

#include <string>
#include <sstream>
#include <vector>
#include "IEntity.hpp"
#include "CollisionBox.hh"

class AEntity :
	public IEntity
{
public:
	AEntity();
	virtual ~AEntity();
	virtual		void			update() = 0;
	virtual		int				getAttack() const;
	virtual		void			setAttack(const int attack);
	virtual		double			getPosX() const;
	virtual		void			setPosX(const double);
	virtual		double			getPosY() const;
	virtual		void			setPosY(const double);
	virtual double			getHeight() const;
	virtual void			setHeight(const double);
	virtual double			getWidth() const;
	virtual void			setWidth(const double);
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
	virtual void			setId(const unsigned int);
	virtual unsigned int	getId() const;
	virtual bool			isDead() const;
	virtual void			setDead(const bool);
	virtual		bool			setArgs(const std::string & args);
	virtual		std::string		getArgs() const;
	virtual CollisionBox		*getCollisionBox() const;
	virtual bool			isColliding(CollisionBox *) const;
	virtual void			refresh();
	virtual void					setA(const int);
	virtual int						getA() const;

protected:
	int						_id;
	bool					_isDead;
	double					_posX;
	double					_speedY;
	double					_speedX;
	double					_posY;
	double					_height;
	double					_width;
	int						_life;
	std::string				_spritePath;
	rtype::EntityType		_type;
	std::string				_name;
	std::string				_args;
	char					_separator;
	CollisionBox			*_collisionBox;
	int						_a;
	int						_attack;

	std::vector<std::string>	split(const std::string & s);
};
