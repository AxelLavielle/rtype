#pragma once

#include			"IGraphManager.hpp"
#include			"IEventManager.hpp"
#include			"Button.hh"
#include			"ListBox.hh"
#include			"InputBox.hh"
#include			"CursorBox.hh"
#include			"CheckBox.hh"
#include			"RectDecor.hh"
#include			"Sound.hh"
#include			"SFMLSound.hh"
#include			"PathFileManager.hh"

class				IPage
{
  virtual			~IPage();
  virtual bool			init() = 0;
  virtual void			clear() = 0;
  virtual bool			launch() = 0;
  virtual void			InitButton(int, int, int, Rect, std::string) = 0;
  virtual void			InitListBox(Rect, std::string, std::string, std::string,  Color) = 0;
  virtual void			InitInputBox(Rect, std::string, Color) = 0;
  virtual void			initCursorBox(Rect, std::string, std::string, Color) = 0;
  virtual void			InitCheckBox(Rect, std::string, std::string, Color) = 0;
  virtual void			initDecor(Rect, std::string) = 0;
  virtual void			initDecor(Rect, std::string, Color) = 0;
  virtual void			drawGUIElement() = 0;

};
