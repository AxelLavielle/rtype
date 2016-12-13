#pragma once

#include <dlfcn.h>
#include <vector>
#include <utility>
#include "IDlLoader.hpp"
#include "IDirectoryBrowser.hpp"

class DlManager
{
public:
	DlManager();
	~DlManager();
	std::string					getFolderPath(void) const;
	void						setFolderPath(const std::string &);
	IEntity						*getdl(const std::string &) const;
	std::vector<std::pair<IEntity*, std::string> >	getAlldl() const;
	void						clearEntities();
	bool	       					refresh();
	void						setBrowser(IDirectoryBrowser *);
	IDirectoryBrowser				*getBrowser();
private:
	std::string					_folderPath;
	IDlLoader      					*_DlLoader;
	std::vector<std::pair<IEntity*, std::string> >	_dl;
  IDirectoryBrowser				*_browser;
};
