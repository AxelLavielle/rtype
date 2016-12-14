//
// Page for Page in /home/laviel_a/
// 
// Made by Axel Lavielle
// Login   <laviel_a@epitech.net>
// 
// Started on  Wed Dec 14 15:41:00 2016 Axel Lavielle
// Last update Wed Dec 14 18:06:42 2016 Axel Lavielle
//

#include	"APage.hh"

APage::APage()
{
	_graph = NULL;
	_event = NULL;
	_soundManager = NULL;
}

APage::APage(IGraphManager *graph, IEventManager *event, const PathFileManager &fileManager, ISoundManager *soundManager)
{
  _graph = graph;
  _event = event;
  _fileManager = fileManager;
  _soundManager = soundManager;
}

APage::~APage()
{

}

void		APage::InitButton(int textPosX, int textPosY, int textSize, Rect pos, std::string name)
{
  Button	button(_graph, _event, pos, name);

  button.setTextPos(textPosX, textPosY);
  button.setTextSize(textSize);
  _buttons.push_back(button);
}

void		APage::InitInputBox(Rect pos, std::string sprite, Color rgb)
{
  InputBox	input(_graph, _event, pos);

  input.setEvent(_event);
  input.setGraph(_graph);
  input.setBackgroundSprite(_fileManager.getRoot() + sprite);
  input.setTextColor(rgb);
  _input.push_back(input);
}

void		APage::initDecor(Rect pos, std::string sprite)
{
  RectDecor	*decor = new RectDecor(_graph, _event, pos);

  decor->setBackgroundSprite(_fileManager.getRoot() + sprite);
  _guiElement.push_back(decor);
}

void		APage::initDecor(Rect pos, std::string sprite, Color rgb)
{
  RectDecor	*decor = new RectDecor(_graph, _event, pos);

  decor->setBackgroundSprite(_fileManager.getRoot() + sprite);
  decor->setTransparentColor(rgb);
  _guiElement.push_back(decor);
}

void		APage::initCursorBox(Rect pos, std::string spriteBar, std::string spriteButton)
{
  CursorBox	cursor(_graph, _event, pos);

  cursor.setBackgroundSprite(_fileManager.getRoot() + spriteBar);
  cursor.setBackgroundOverSprite(_fileManager.getRoot() + spriteButton);
  _cursorBox.push_back(cursor);
}

void		APage::InitCheckBox(Rect pos, std::string spriteEmpty, std::string spriteFill)
{
  CheckBox	check(_graph, _event, pos);

  check.setBackgroundSprite(_fileManager.getRoot() + spriteEmpty);
  check.setCheckedSprite(_fileManager.getRoot() + spriteFill);
  _checkBox.push_back(check);
}

void		APage::InitListBox(Rect pos, std::string font, std::string button, std::string hover)
{
  ListBox	list(_graph, _event, pos);

  list.setFontPath(_fileManager.getRoot() + font);
  list.setButtonSprite(_fileManager.getRoot() + button);
  list.setButtonOverSprite(_fileManager.getRoot() + hover);
  _listBox.push_back(list);
}

void		APage::drawGUIElement()
{
  std::vector<AGUIElement*>::iterator		it;

  it = _guiElement.begin();
  while (it != _guiElement.end())
    {
      (*it)->draw();
      ++it;
    }
}
