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
public:
  enum PAGE
    {
      HOME,
      SAVE,
      PLAY,
      CREATEROOM,
      INSIDEROOM,
      SETTINGS,
      QUIT,
      GAME,
      ENDGAME,
      PAUSE,
      CREATEROOMACTION,
      NONE
    };

  virtual			~IPage() {}
  virtual bool			init() = 0;
  virtual void			clear() = 0;
  virtual bool			launch() = 0;
  virtual void			draw() = 0;
  virtual IPage::PAGE	event() = 0;
  virtual IPage::PAGE getPageType() const = 0;
};
