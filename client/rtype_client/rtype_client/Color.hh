#pragma once

class Color
{
public:
	Color(const int &r, const int &g, const int &b, const int &a = 255);
	Color();
	int getR() const;
	int getG() const;
	int getB() const;
	int getA() const;
	int setR(const int r) const;
	int setG(const int g) const;
	int setB(const int b) const;
	int setA(const int a) const;
private:
	int		_r;
	int		_g;
	int		_b;
	int		_a;
};