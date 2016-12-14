#pragma once

#include	"IPage.hpp"

class		APage
{
public:
  APage();
  APage(IGraphManager*, IEventManager*, const PathFileManager &);
  virtual			~APage();
  virtual bool			init() = 0;
  virtual void			clear() = 0;
  virtual bool			launch() = 0;
  virtual void			InitButton(int, int, int, Rect, std::string);
  virtual void			InitListBox(Rect, std::string, std::string, std::string);
  virtual void			InitInputBox(Rect, std::string, Color);
  virtual void			initCursorBox(Rect, std::string, std::string);
  virtual void			InitCheckBox(Rect, std::string, std::string);
  virtual void			initDecor(Rect, std::string);
  virtual void			initDecor(Rect, std::string, Color);
  virtual void			drawGUIElement();

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
};
