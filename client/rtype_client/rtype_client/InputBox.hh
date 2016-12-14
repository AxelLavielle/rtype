#pragma once

#include "AGUIElement.hh"

class InputBox : public AGUIElement
{
public:
	InputBox(IGraphManager *graph, IEventManager *event, const Rect &rect);
	InputBox();
	virtual ~InputBox();
	virtual bool draw();
	virtual bool click();
	virtual bool over();
	std::string getText() const;
	bool getInput();
	void setTextColor(const Color & color);
	void setGraph(IGraphManager *graph);
	void setEvent(IEventManager *event);

private:
	std::string		_key;
	Color			_textColor;
};

