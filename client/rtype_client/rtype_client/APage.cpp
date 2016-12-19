//
// Page for Page in /home/laviel_a/
// 
// Made by Axel Lavielle
// Login   <laviel_a@epitech.net>
// 
// Started on  Wed Dec 14 15:41:00 2016 Axel Lavielle
// Last update Sat Dec 17 01:19:49 2016 Axel Lavielle
//

#include	"APage.hh"

APage::APage()
{
	_graph = NULL;
	_event = NULL;
	_soundManager = NULL;
	_windowSize.first = 0;
	_windowSize.second = 0;
	_pageType = IPage::NONE;
}

APage::APage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager)
{
  _graph = graph;
  _event = event;
  _fileManager = fileManager;
  _soundManager = soundManager;
  _backgroundSprite = "";
  _windowSize = _graph->getWindowSize();
  _pageType = IPage::NONE;
}

APage::~APage()
{

}

IPage::PAGE APage::getPageType() const
{
	return (_pageType);
}


void		APage::initButton(const int textPosX, const int textPosY, const int textSize,
								const Rect &pos, const std::string &name, const std::string &sprite,
								const std::string &spriteHover, const std::string &fontPath, IPage::PAGE page)
{
  Button	*button = new Button(_graph, _event, pos, name);

  button->setTextPos(textPosX, textPosY);
  button->setTextSize(textSize);
  button->setBackgroundSprite(_fileManager.getRoot() + sprite);
  button->setBackgroundOverSprite(_fileManager.getRoot() + spriteHover);
  button->setFontPath(_fileManager.getRoot() + fontPath);
  _buttons.insert(std::pair<IPage::PAGE, AGUIElement *>(page, button));
}

void		APage::initButton(const int textPosX, const int textPosY, const int textSize,
								const Rect &pos, const std::string &name, const std::string &sprite,
								const std::string &spriteHover, const std::string &fontPath)
{
	Button	*button = new Button(_graph, _event, pos, name);

	button->setTextPos(textPosX, textPosY);
	button->setTextSize(textSize);
	button->setBackgroundSprite(_fileManager.getRoot() + sprite);
	button->setBackgroundOverSprite(_fileManager.getRoot() + spriteHover);
	button->setFontPath(_fileManager.getRoot() + fontPath);
	_guiElement.push_back(button);
}

void		APage::initInputBox(const Rect &pos, const std::string &sprite, const Color &rgb)
{
  InputBox	*input = new InputBox(_graph, _event, pos);

  input->setEvent(_event);
  input->setGraph(_graph);
  input->setBackgroundSprite(_fileManager.getRoot() + sprite);
  input->setFontPath(_fileManager.getRoot() + "/res/fonts/OpenSans-Regular.ttf");
  input->setTextColor(rgb);
  _guiElement.push_back(input);
}

void		APage::initDecor(const Rect &pos, const std::string &sprite)
{
  RectDecor	*decor = new RectDecor(_graph, _event, pos);

  decor->setBackgroundSprite(_fileManager.getRoot() + sprite);
  _guiElement.push_back(decor);
}

void		APage::initDecor(const Rect &pos, const std::string &sprite, const Color &rgb)
{
  RectDecor	*decor = new RectDecor(_graph, _event, pos);

  decor->setBackgroundSprite(_fileManager.getRoot() + sprite);
  decor->setTransparentColor(rgb);
  _guiElement.push_back(decor);
}

void		APage::initCursorBox(const Rect &pos, const std::string &spriteBar, const std::string &spriteButton)
{
  CursorBox	*cursor = new CursorBox(_graph, _event, pos);

  cursor->setBackgroundSprite(_fileManager.getRoot() + spriteBar);
  cursor->setBackgroundOverSprite(_fileManager.getRoot() + spriteButton);
  _guiElement.push_back(cursor);
}

void		APage::initCheckBox(const Rect &pos, const std::string &spriteEmpty, const std::string &spriteFill)
{
  CheckBox	*check = new CheckBox(_graph, _event, pos);

  check->setBackgroundSprite(_fileManager.getRoot() + spriteEmpty);
  check->setCheckedSprite(_fileManager.getRoot() + spriteFill);
  _guiElement.push_back(check);
}

void		APage::initListBox(const Rect &pos, const std::string &font, const std::string &button, const std::string &hover, const std::vector<std::string> &elements)
{
  ListBox	*list = new ListBox(_graph, _event, pos);

  list->setFontPath(_fileManager.getRoot() + font);
  list->setButtonSprite(_fileManager.getRoot() + button);
  list->setButtonOverSprite(_fileManager.getRoot() + hover);
  list->setElements(elements);
  _guiElement.push_back(list);
}

void		APage::drawGUIElement(std::vector<AGUIElement *> guiElements)
{
  std::vector<AGUIElement*>::iterator		it;

  it = guiElements.begin();
  while (it != guiElements.end())
    {
      (*it)->draw();
      ++it;
    }
}

void APage::clearGUIElement(std::vector<AGUIElement*> guiElements)
{
	std::vector<AGUIElement * >::iterator			it;

	it = guiElements.begin();
	while (it != guiElements.end())
	{
		delete (*it);
		++it;
	}
	guiElements.clear();
}

void APage::hoverEvent(std::vector<AGUIElement*> guiElements)
{
	std::vector<AGUIElement * >::iterator			it;

	it = guiElements.begin();
	while (it != guiElements.end())
	{
		(*it)->over();
		++it;
	}
}

void APage::drawGUIElement(std::map<IPage::PAGE, AGUIElement* > guiElements)
{
	std::map<IPage::PAGE, AGUIElement* >::iterator			it;

	it = guiElements.begin();;
	while (it != guiElements.end())
	{
		it->second->draw();
		++it;
	}
}

void APage::clearGUIElement(std::map<IPage::PAGE, AGUIElement*> guiElements)
{
	std::map<IPage::PAGE, AGUIElement* >::iterator			it;

	it = guiElements.begin();;
	while (it != guiElements.end())
	{
		delete (it->second);
		++it;
	}
	guiElements.clear();
}

void APage::hoverEvent(std::map<IPage::PAGE, AGUIElement*> guiElements)
{
	std::map<IPage::PAGE, AGUIElement* >::iterator			it;

	it = guiElements.begin();;
	while (it != guiElements.end())
	{
		it->second->over();
		++it;
	}
}

IPage::PAGE APage::clickEvent(std::map<IPage::PAGE, AGUIElement*> guiElements)
{
	std::map<IPage::PAGE, AGUIElement* >::iterator			it;

	it = guiElements.begin();
	while (it != guiElements.end())
	{
		if (it->second->click())
		  {
		    return (it->first);
		  }
		++it;
	}
	return (IPage::NONE);
}

void APage::clickEvent(std::vector<AGUIElement*> guiElements)
{
  unsigned int		i;

  i = 0;
  while (i != guiElements.size())
    {
      if (guiElements[i]->click())
	{
	  return;
	}
      i++;
    }
}
