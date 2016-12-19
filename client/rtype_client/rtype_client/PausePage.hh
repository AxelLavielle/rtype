#pragma once

#include "APage.hh"

class PausePage :
	public APage
{
public:
  PausePage();
  PausePage(IGraphManager*, IEventManager*, const PathFileManager&, ISoundManager*);
  virtual ~PausePage();
  virtual bool			init();
  virtual void			clear();
  virtual bool			launch();
  virtual void			draw();
  virtual IPage::PAGE		event();

private:
  Sound				_clickSound;

};

