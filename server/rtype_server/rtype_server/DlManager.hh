#pragma once

#include <dlfcn.h>
#include <vector>
#include <utility>
#include "DlLoader.hh"
#include "DirectoryBrowser.hh"

class DlManager
{
public:
	DlManager();
	~DlManager();
  bool							init();
	std::string					getFolderPath(void) const;
	void						setFolderPath(const std::string &);
	IEntity						*getdl(const std::string &) const;
	std::vector<std::pair<IEntity*, std::string> >	getAlldl() const;
	void						clearEntities();
	bool	       					refresh();
	void						setBrowser(IDirectoryBrowser *);
	IDirectoryBrowser				*getBrowser() const;
	bool						loadEntities(const std::vector<std::string>&);
	bool						loadEntity(const std::string &path);
private:
	std::string					_folderPath;
	IDlLoader      					*_DlLoader;
	std::vector<std::pair<IEntity*, std::string> >	_dl;
	IDirectoryBrowser				*_browser;
};
