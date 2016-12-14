#include "DlManager.hh"
#include "UWDlLoader.hh"
#include "UWDirectoryBrowser.hh"
#include <iostream>

DlManager::DlManager()
{
  _DlLoader = new UWDlLoader();
  _browser = new UWDirectoryBrowser();
}

DlManager::~DlManager()
{
}

std::string						DlManager::getFolderPath() const
{
 return (_folderPath);
}

void							DlManager::setFolderPath(const std::string &path)
{
  this->getBrowser()->setPath(path);
  this->refresh();
}

IEntity							*DlManager::getdl(const std::string &dlname) const
{
  for (std::vector<std::pair<IEntity*, std::string> >::const_iterator it = _dl.begin(); it != _dl.end(); it++)
    {
      if (it->second.compare(dlname) == 0)
	return (it->first);
    }
  return (NULL);
}

std::vector<std::pair<IEntity*, std::string> > 		DlManager::getAlldl() const
{
  return (_dl);
}

bool							DlManager::refresh()
{
  this->clearEntities();
  this->getBrowser()->refresh();
  this->loadEntities(this->getBrowser()->getFiles());
  return (true);
}

void							DlManager::clearEntities()
{
  _dl.clear();
}

IDirectoryBrowser					*DlManager::getBrowser()
{
  return (_browser);
}

void							DlManager::setBrowser(IDirectoryBrowser *DB)
{
  _browser = DB;
}

bool							DlManager::loadEntities(const std::vector<std::string> &files)
{
  if (files.size() == 0)
    return (false);
  for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); it++)
    {
      IEntity		*tmp;
      std::cout << "adding " << *it << std::endl;
      _DlLoader->load(*it);
      tmp = _DlLoader->getInstance();
      if (tmp)
	_dl.push_back(std::pair<IEntity*, std::string>(tmp, tmp->getName()));
    }
  this->getBrowser()->clear();
  return (true);
}
