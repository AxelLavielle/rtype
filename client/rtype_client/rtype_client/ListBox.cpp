#include "ListBox.hh"



ListBox::ListBox(IGraphManager *graph, IEventManager *event, const Rect &rect)
{
	_graph = graph;
	_event = event;
	_rect = rect;
	_height = 30;
}


ListBox::~ListBox()
{
}

void	ListBox::drawButton()
{
	std::vector<Button>::iterator	it;
	int i;

	i = 0;
	it = _buttons.begin();
	while (it != _buttons.end())
	{
		it->draw();
		++it;
	}
}

bool ListBox::draw()
{
	_graph->drawRectangle("../../res/img/button.jpg", _rect);
	drawButton();
	return (true);
}

void ListBox::setElements(const std::vector<std::string>& elements)
{
	std::vector<std::string>::const_iterator	it;
	unsigned int								i;

	i = 0;
	it = elements.begin();
	while (it != elements.end())
	{
		Button tmp(_graph, _event, Rect(_rect.getX() + 10, _rect.getY() + 10 + (_height + 10) * i, _height, _rect.getWidth() - 20), *it);

		tmp.setBackgroundColor(Color(0, 0, 255));
		tmp.setTextPos(20, 0);
		tmp.setTextSize(25);
		_buttons.push_back(tmp);
		++it;
		i++;
	}
	_elements = elements;
}
