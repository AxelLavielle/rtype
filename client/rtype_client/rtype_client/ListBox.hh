#pragma once

#include <vector>
#include <sstream>
#include "Button.hh"
#include "AGUIElement.hh"

class ListBox : public AGUIElement
{
public:
	ListBox(IGraphManager *graph, IEventManager *event, const Rect &rect);
	~ListBox();
	virtual bool draw();
	virtual bool over();
	void setElements(const std::vector<std::string> &elements);
	virtual bool click();
	int getSelectedID(void) const;
	void setButtonSprite(const std::string & sprite);
	void setButtonOverSprite(const std::string & sprite);

private:
	void drawButton();

	std::vector<std::string>	_elements;
	std::vector<Button>			_buttons;
	Button						_nextButton;
	Button						_prevButton;
	unsigned int				_height;
	int							_currentPage;
	int							_selectedID;
	std::string					_buttonSprite;
	std::string					_buttonOverSprite;
};

