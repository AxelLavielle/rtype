#pragma once

#include	"IPage.hpp"
#include	"Sound.hh"

class		APage
{
public:
  APage();
  APage(IGraphManager*, IEventManager*, const PathFileManager &, ISoundManager *soundManager);
  virtual			~APage();
  virtual bool			init() = 0;
  virtual void			clear() = 0;
  virtual bool			launch() = 0;
  virtual void			draw() = 0;
  virtual IPage::PAGE	event() = 0;
  virtual IPage::PAGE	getPageType() const;

protected:
  std::map<IPage::PAGE, AGUIElement* >		_buttons;
  std::vector<AGUIElement* >		_listBox;
  std::vector<AGUIElement* >		_input;
  std::vector<AGUIElement* >		_cursorBox;
  std::vector<AGUIElement* >		_checkBox;
  std::vector<AGUIElement* >		_guiElement;
  IGraphManager						*_graph;
  IEventManager						*_event;
  PathFileManager					_fileManager;
  ISoundManager						*_soundManager;
  std::string						_backgroundSprite;
  std::pair<int, int>				_windowSize;
  IPage::PAGE						_pageType;

  void			initButton(const int textPosX, const int textPosY, const int textSize, const Rect & pos, const std::string & name, const std::string & sprite, const std::string & spriteHover, const std::string & fontPath, IPage::PAGE page);
  void			initButton(const int textPosX, const int textPosY, const int textSize, const Rect & pos, const std::string & name, const std::string & sprite, const std::string & spriteHover, const std::string & fontPath);
  void			initInputBox(const Rect & pos, const std::string & sprite, const Color & rgb);
  void			initInputBox(const Rect & pos, const std::string & sprite, const Color & rgb, const std::string &inputText);
  void			initDecor(const Rect & pos, const std::string & sprite);
  void			initDecor(const Rect & pos, const std::string & sprite, const Color & rgb);
  void			initCursorBox(const Rect & pos, const std::string & spriteBar, const std::string & spriteButton);
  void			initCheckBox(const Rect & pos, const std::string & spriteEmpty, const std::string & spriteFill);
  void			initListBox(const Rect & pos, const std::string & font, const std::string & button, const std::string & hover, const std::vector<std::string>& elements);
  void			drawGUIElement(std::vector<AGUIElement *> guiElements);
  void			clearGUIElement(std::vector<AGUIElement *> guiElements);
  void			hoverEvent(std::vector<AGUIElement *> guiElements);
  void			drawGUIElement(std::map<IPage::PAGE, AGUIElement *> guiElements);
  void			clearGUIElement(std::map<IPage::PAGE, AGUIElement *> guiElements);
  void			hoverEvent(std::map<IPage::PAGE, AGUIElement *> guiElements);
  void			clickEvent(std::vector<AGUIElement*> guiElements);
  IPage::PAGE		clickEvent(std::map<IPage::PAGE, AGUIElement *> guiElements);
};
