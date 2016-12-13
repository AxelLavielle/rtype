#pragma once

class Rect
{
public:
	Rect();
	Rect(const int x, const int y, const int height, const int width);
	Rect(const Rect &r);
	~Rect();
	int getX() const;
	int getY() const;
	int getHeight() const;
	int getWidth() const;
	void setX(const int x);
	void setY(const int y);
	void setHeight(const int height);
	void setWidth(const int width);

	Rect &operator=(const Rect &r);
private:
	int _x;
	int _y;
	int _height;
	int _width;
};
