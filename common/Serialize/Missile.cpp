#include "Missile.hh"

Missile::Missile(const int x, const int y, const int idPlayer)
{
	this->setType(rtype::MISSILE);
	this->setName("");
	this->setPosX(x);
	this->setPosY(y);
	this->setHeight(2);
	this->setWidth(3);
	this->setSpeedX(3);
	this->setSpeedY(0);
	this->setLife(100);
	this->setSpriteRepo("/res/img/missile" + std::to_string(idPlayer) + ".png");
	_collisionBox = new CollisionBox(this);
	_idPlayer = idPlayer;
	refresh();
}

Missile::~Missile()
{
}

void	Missile::update()
{
	setPosX(_posX + _speedX);
	setPosY(_posY + _speedY);
	refresh();
}

int		Missile::getIdPlayer() const
{
	return (_idPlayer);
}