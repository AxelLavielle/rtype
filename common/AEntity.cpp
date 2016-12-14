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

double			AEntity::getPosX(void) const
{
  return (_posX);
}

void			AEntity::setPosY(const double posY)
{
  _posY = posY;
}

double			AEntity::getPosY(void) const
{
  return (_posY);
}

void			AEntity::update(void)
{
}

void			AEntity::setType(const rtype::EntityType &type)
{
  _type = type;
}

rtype::EntityType	AEntity::getType(void) const
{
  return (_type);
}

IEntity			*AEntity::entityCreator()
{
  return (NULL);
}
