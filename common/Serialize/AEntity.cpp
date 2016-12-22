#include "AEntity.hh"

AEntity::AEntity()
{
	_posX = -1;
	_posY = -1;
	_type = rtype::ABSTRACT;
	_speedX = -1;
	_speedY = -1;
	_name = "ABSTRACT";
	_spritePath = "";
	_life = -1;
	_height = -1;
	_width = -1;
}

AEntity::~AEntity()
{
}

void			AEntity::setPosX(const double posX)
{
  _posX = posX;
}

double			AEntity::getPosX() const
{
  return (_posX);
}

void			AEntity::setPosY(const double posY)
{
  _posY = posY;
}

double AEntity::getHeight() const
{
	return (_height);
}

void AEntity::setHeight(const double height)
{
	_height = height;
}

double AEntity::getWidth() const
{
	return (_width);
}

void AEntity::setWidth(const double width)
{
	_width = width;
}

double			AEntity::getPosY() const
{
  return (_posY);
}

void			AEntity::setType(const rtype::EntityType &type)
{
  _type = type;
}

rtype::EntityType	AEntity::getType() const
{
  return (_type);
}

std::string		AEntity::getName() const
{
  return (_name);
}

void			AEntity::setName(const std::string &name)
{
  _name = name;
}
#include <iostream>
void			AEntity::setSpriteRepo(const std::string &path)
{
  _spritePath = path;
  std::cout << "SET = " << _spritePath << std::endl;
}

std::string		AEntity::getSpriteRepo() const
{
	std::cout << "GET = " << _spritePath << std::endl;
  return (_spritePath);
}

double			AEntity::getSpeedX() const
{
  return (_speedX);
}

void			AEntity::setSpeedX(const double speedX)
{
  _speedX = speedX;
}

double			AEntity::getSpeedY() const
{
  return (_speedY);
}

void			AEntity::setSpeedY(const double speedY)
{
  _speedY = speedY;
}

int			AEntity::getLife() const
{
  return (_life);
}

void			AEntity::setLife(const int life)
{
  _life = life;
}
