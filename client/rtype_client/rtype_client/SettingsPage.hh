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
  std::pair<std::string, std::pair<int, int> > save() const;

private:
  Sound				_clickSound;

};

