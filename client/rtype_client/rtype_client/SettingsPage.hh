#pragma once

#include "APage.hh"
#include "SaveConfig.hh"

class SettingsPage :
	public APage
{
public:
  SettingsPage();
  SettingsPage(IGraphManager*, IEventManager*, const PathFileManager&, ISoundManager*);
  virtual ~SettingsPage();
  void setServerInfo(const std::string & ip, const int port);
  virtual bool			init();
  virtual void			clear();
  virtual bool			launch();
  virtual void			draw();
  std::pair<std::string, int> getServerInfo() const;
  virtual IPage::PAGE		event();
  std::pair<std::string, std::pair<int, int> > save() const;

private:
  void				manageConfigs();

  Sound				_clickSound;
  std::string		_ip;
  std::string		_port;

};

