#pragma once

#include <iostream>
#include "AGUIElement.hh"

class Button : public AGUIElement
{
public:
	Button(IGraphManager *graph, IEventManager *event, const Rect &rect, const std::string &txt);
	Button();
	~Button();
	virtual bool draw();
	virtual bool over();
	virtual bool click();
	void setBackgroundColor(const Color & color);
	void setBackgroundColorOver(const Color & color);
	void setTextPos(const int &x, const int &y);
	void setTextSize(const int &size);
	void setText(const std::string &txt);
private:
	std::string			_txt;
	Color				_backgroundColor;
	Color				_backgroundColorOver;

	int					_textSize;
	int					_posXText;
	int					_posYText;
	bool				_over;
};