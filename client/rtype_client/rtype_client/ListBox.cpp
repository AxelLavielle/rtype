#include "ListBox.hh"



ListBox::ListBox(IGraphManager *graph, IEventManager *event, const Rect &rect) : AGUIElement(graph, event, rect)
{
	_selectedID = -1;
	_height = 30;
	_currentPage = 0;
	_buttonOverSprite = "";
	_buttonSprite = "";
	_nextButton.setGraph(graph);
	_prevButton.setGraph(graph);
	_nextButton.setEvent(event);
	_prevButton.setEvent(event);
	_nextButton.setBackgroundColor(Color(255, 255, 255, 0));
	_prevButton.setBackgroundColor(Color(255, 255, 255, 0));
	_prevButton.setBackgroundOverColor(Color(255, 255, 255, 0));
	_nextButton.setBackgroundOverColor(Color(255, 255, 255, 0));
	_nextButton.setPos(Rect(rect.getX() + rect.getWidth() - 70, rect.getY() + rect.getHeight() + 10, 20, 70));
	_prevButton.setPos(Rect(rect.getX() + rect.getWidth() - 200, rect.getY() + rect.getHeight() + 10, 20, 70));
	_nextButton.setText("Next");
	_prevButton.setText("Prev");
	_nextButton.setTextPos(10, 0);
	_nextButton.setTextSize(15);
	_prevButton.setTextPos(10, 0);
	_prevButton.setTextSize(15);
	_typeName = "ListBox";
}


ListBox::~ListBox()
{
}

void ListBox::setFontPath(const std::string & path)
{
	_fontPath = path;
	_nextButton.setFontPath(_fontPath);
	_prevButton.setFontPath(_fontPath);
}

void	ListBox::drawButton()
{
	std::vector<Button>::iterator	it;
	unsigned int i;

	i = 0;
	it = _buttons.begin();
	while (it != _buttons.end() && i != (_rect.getHeight() / (_height + 10)) * _currentPage)
	{
		++it;
		i++;
	}
	while (it != _buttons.end() && i < (_rect.getHeight() / (_height + 10)) * (_currentPage + 1))
	{
		it->draw();
		it->over();
		++it;
		i++;
	}

}

bool	ListBox::click()
{
	int	i;
	int max;
	std::vector<Button>::iterator	it;

	if (_elements.size() <= 0)
		return (false);
	max = _elements.size() / (_rect.getHeight() / (_height + 10));
	if (_elements.size() % (_rect.getHeight() / (_height + 10)))
		max++;
	it = _buttons.begin();
	_selectedID = -1;
	i = 0;
	while (it != _buttons.end() && static_cast<unsigned int>(i) != (_rect.getHeight() / (_height + 10)) * _currentPage)
	{
		++it;
		i++;
	}
	while (it != _buttons.end())
	{
		if (it->click())
		{
			_selectedID = i;
			return (true);
		}
		++it;
		i++;
	}
	if (_nextButton.click())
		_currentPage = (_currentPage + 1) % max;
	else if (_prevButton.click())
		_currentPage = (_currentPage - 1);
	if (_currentPage < 0)
		_currentPage = max - 1;
	if (_selectedID != -1)
		return (true);
	return (false);
}

int ListBox::getSelectedID(void) const
{
	return (_selectedID);
}

void ListBox::setButtonSprite(const std::string & sprite)
{
	_buttonSprite = sprite;
}

void ListBox::setButtonOverSprite(const std::string & sprite)
{
	_buttonOverSprite = sprite;
}

bool ListBox::draw()
{
	std::stringstream ss;
	int max;

	max = _elements.size() / (_rect.getHeight() / (_height + 10));
	if (_elements.size() % (_rect.getHeight() / (_height + 10)))
		max++;

	//	_graph->drawRectangle("../../res/img/button.jpg", _rect);

	drawButton();
	if (_elements.size() > 0)
	{
		_nextButton.draw();
		_prevButton.draw();
		ss << _currentPage + 1 << " / " << max;
		_graph->drawText(ss.str(), _rect.getX() + _rect.getWidth() - 120, _rect.getY() + _rect.getHeight() + 10, 20, Color(255, 255, 255), _fontPath);
	}
	return (true);
}

bool ListBox::over()
{
	if (_elements.size() > 0)
	{
		_nextButton.over();
		_prevButton.over();
	}
	return (false);
}

void ListBox::setElements(const std::vector<std::string>& elements)
{
	std::vector<std::string>::const_iterator	it;
	unsigned int								i;
	unsigned int								max;

	i = 0;
	max = (_rect.getHeight() / (_height + 10));
	it = elements.begin();
	while (it != elements.end())
	{
		Button tmp(_graph, _event, Rect(_rect.getX() + 10, _rect.getY() + 10 + (_height + 10) * (i % max), _height, _rect.getWidth() - 20), *it);

		tmp.setBackgroundSprite(_buttonSprite);
		tmp.setBackgroundOverSprite(_buttonOverSprite);
		tmp.setTextPos(20, 0);
		tmp.setTextSize(25);
		tmp.setFontPath(_fontPath);
		_buttons.push_back(tmp);
		++it;
		i++;
	}
	_elements = elements;
}
