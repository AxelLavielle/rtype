#include "Missile.hh"

#include <iostream>

Missile::Missile(const int x, const int y)
{
	this->setType(rtype::MISSILE);
	this->setName("");
	this->setPosX(x);
	this->setPosY(y);
	this->setHeight(2);
	this->setWidth(3);
	this->setSpeedX(1);
	this->setSpeedY(1);
	this->setLife(100);
	this->setSpriteRepo("/res/img/shipMissileBlue.png");
}

Missile::~Missile()
{
	std::cout << "MISSILE DESTROYED" << std::endl;
}

void	Missile::update()
{
	std::cout << "Moving missile : " << std::endl;
		//<< _posX << " to " << _posX + _speedX << std::endl;
	//setPosX(_posX + _speedX);
	//refresh();
}