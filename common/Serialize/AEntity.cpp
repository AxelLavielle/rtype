#include "AEntity.hh"

AEntity::AEntity()
{
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

void			AEntity::setSpriteRepo(const std::string &path)
{
  _spritePath = path;
}

std::string		AEntity::getSpriteRepo() const
{
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
