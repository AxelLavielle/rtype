#pragma once

#include	"IPage.hpp"

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

protected:
  std::vector<AGUIElement* >		_buttons;
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

  void			initButton(const int textPosX, const int textPosY, const int textSize, const Rect & pos, const std::string & name, const std::string & sprite, const std::string & spriteHover, const std::string & fontPath);
  void			initListBox(Rect, std::string, std::string, std::string);
  void			initInputBox(Rect, std::string, Color);
  void			initCursorBox(Rect, std::string, std::string);
  void			initCheckBox(Rect, std::string, std::string);
  void			initDecor(Rect, std::string);
  void			initDecor(Rect, std::string, Color);
  void			drawGUIElement(std::vector<AGUIElement *> guiElements);
  void			clearGUIElement(std::vector<AGUIElement *> guiElements);
  void			hoverEvent(std::vector<AGUIElement *> guiElements);
};
