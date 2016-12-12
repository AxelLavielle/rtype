#include "Rect.hh"

Rect::Rect()
{

}

Rect::Rect(const int & x, const int & y, const int & height, const int & width)
{
	_x = x;
	_y = y;
	_height = height;
	_width = width;
}

Rect::~Rect()
{
}

Rect::Rect(const Rect &r)
{
	_x = r.getX();
	_y = r.getY();
	_height = r.getHeight();
	_width = r.getWidth();
}

int Rect::getX() const
{
	return (_x);
}

int Rect::getY() const
{
	return (_y);
}

int Rect::getHeight() const
{
	return (_height);
}

int Rect::getWidth() const
{
	return (_width);
}

void Rect::setX(const int x)
{
	_x = x;
}

void Rect::setY(const int y)
{
	_y = y;
}

void Rect::setHeight(const int height)
{
	_height = height;
}

void Rect::setWidth(const int width)
{
	_width = width;
}

Rect & Rect::operator=(const Rect & r)
{
	_x = r.getX();
	_y = r.getY();
	_height = r.getHeight();
	_width = r.getWidth();
	return (*this);
}
