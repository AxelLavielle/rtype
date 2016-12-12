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
	void setR(const int r);
	void setG(const int g);
	void setB(const int b);
	void setA(const int a);
private:
	int		_r;
	int		_g;
	int		_b;
	int		_a;
};
