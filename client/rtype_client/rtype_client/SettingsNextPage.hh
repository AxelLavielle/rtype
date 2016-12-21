#pragma once

#include "APage.hh"

class SettingsNextPage :
	public APage
{
public:
  SettingsNextPage();
  SettingsNextPage(IGraphManager*, IEventManager*, const PathFileManager&, ISoundManager*);
  virtual ~SettingsNextPage();
  virtual bool			init();
  virtual void			clear();
  virtual bool			launch();
  virtual void			draw();
  virtual IPage::PAGE		event();
  std::pair<std::string, std::pair<int, int> > save() const;

private:
  Sound				_clickSound;

};

