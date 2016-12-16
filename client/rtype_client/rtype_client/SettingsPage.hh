#pragma once

#include "APage.hh"

class SettingsPage :
	public APage
{
public:
  SettingsPage();
  SettingsPage(IGraphManager*, IEventManager*, const PathFileManager&, ISoundManager*);
  virtual ~SettingsPage();
  virtual bool			init();
  virtual void			clear();
  virtual bool			launch();
  virtual void			draw();
  virtual IPage::PAGE		event();

private:
  Sound				_clickSound;

};

