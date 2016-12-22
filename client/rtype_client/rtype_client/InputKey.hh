#pragma once

#include "AGUIElement.hh"

class InputKey : public AGUIElement
{
public:
	InputKey(IGraphManager *graph, IEventManager *event, const Rect &rect);
	InputKey();
	void setText(const std::string & text);
	virtual ~InputKey();
	virtual bool draw();
	virtual bool click();
	virtual bool over();
	std::string getText() const;
	bool getInput();
	void setTextColor(const Color & color);
	void setGraph(IGraphManager *graph);
	void setEvent(IEventManager *event);

private:
  bool			_focus;
  std::string		_key;
  Color			_textColor;
};

