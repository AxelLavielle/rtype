#include "Monster.hh"

Monster::Monster()
{}

Monster::Monster(const int x, const int y)
{
  this->setType(rtype::MONSTER);
  _name = "Monster1";
  this->setName("");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(2);
  this->setWidth(3);
  this->setSpeedX(1);
  this->setSpeedY(1);
  this->setLife(100);
  this->setSpriteRepo("/res/img/monster.png");
}

Monster::~Monster()
{
}

void		Monster::update()
{
}

extern "C" IEntity	*createEntity()
{
  return (new Monster);
}
