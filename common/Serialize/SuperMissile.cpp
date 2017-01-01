#include "SuperMissile.hh"

SuperMissile::SuperMissile(const int x, const int y, const int idPlayer)
{
	this->setType(rtype::MISSILE);
	this->setName("");
	this->setPosX(x);
	this->setPosY(y);
	this->setHeight(10);
	this->setWidth(10);
	this->setSpeedX(2);
	this->setSpeedY(0);
	this->setLife(1);
	this->setAttack(200);
	this->setSpriteRepo("/res/img/superMissile" + std::to_string(idPlayer) + ".png");
	_collisionBox = new CollisionBox(this);
	_idPlayer = idPlayer;
	refresh();
}

SuperMissile::~SuperMissile()
{
}

void	SuperMissile::update()
{
	setPosX(_posX + _speedX);
	setPosY(_posY + _speedY);
	refresh();
}

int		SuperMissile::getIdPlayer() const
{
	return (_idPlayer);
}