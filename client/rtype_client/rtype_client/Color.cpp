#include "Color.hh"

Color::Color(const int & r, const int & g, const int & b, const int & a)
{
	_r = r;
	_g = g;
	_b = b;
	_a = a;
}

Color::Color()
{
	_r = -1;
	_g = -1;
	_b = -1;
	_a = 255;
}

int Color::getR() const
{
	return (_r);
}

int Color::getG() const
{
	return (_g);
}

int Color::getB() const
{
	return (_b);
}

int Color::getA() const
{
	return (_a);
}

void Color::setR(const int r)
{
	_r = r;
}

void Color::setG(const int g)
{
	_g = g;
}

void Color::setB(const int b)
{
	_b = b;
}

void Color::setA(const int a)
{
	_a = a;
}
