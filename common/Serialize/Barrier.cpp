#include "Barrier.hh"

Barrier::Barrier(const int x, const int y)
{
  this->setType(rtype::BARRIER);
  this->setName("");
  this->setPosX(x);
  this->setPosY(y);
  this->setHeight(5);
  this->setWidth(5 * 5);
  this->setSpeedX(-1);
  this->setSpeedY(0);
  this->setLife(100);
  this->setSpriteRepo("/res/img/spikyWallH.png");
  _collisionBox = new CollisionBox(this);
  refresh();
}

Barrier::~Barrier()
{
}

void	Barrier::update()
{
	setPosX(_posX + _speedX);
	refresh();
}
