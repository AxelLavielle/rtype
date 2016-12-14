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

private:
  std::vector<Button>		_buttons;
  std::vector<ListBox>		_listBox;
  std::vector<InputBox>		_input;
  std::vector<CursorBox>	_cursorBox;
  std::vector<CheckBox>		_checkBox;
  std::vector<AGUIElement*>	_guiElement;
  IGraphManager			*_graph;
  IEventManager			*_event;
  PathFileManager		_fileManager;
  ISoundManager			*_soundManager;

  void			InitButton(int, int, int, Rect, std::string);
  void			InitListBox(Rect, std::string, std::string, std::string);
  void			InitInputBox(Rect, std::string, Color);
  void			initCursorBox(Rect, std::string, std::string);
  void			InitCheckBox(Rect, std::string, std::string);
  void			initDecor(Rect, std::string);
  void			initDecor(Rect, std::string, Color);
  void			drawGUIElement(std::vector<AGUIElement *> guiElements);
};
