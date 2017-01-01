#include "SuperMissile.hh"

SuperMissile::SuperMissile(const int x, const int y, const int idPlayer)
{
	this->setType(rtype::SUPER_MISSILE);
	this->setName("");
	this->setPosX(x);
	this->setPosY(y);
	this->setHeight(3);
	this->setWidth(4);
	this->setSpeedX(2);
	this->setSpeedY(0);
	this->setLife(1);
	this->setAttack(200);
	this->setSpriteRepo("/res/img/SuperMissile" + std::to_string(idPlayer) + ".png");
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