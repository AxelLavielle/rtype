#include "DlManager.hh"
#include "DlLoader.hh"
#include "DirectoryBrowser.hh"
#include <iostream>

DlManager::DlManager()
{
  this->init();
}

DlManager::~DlManager()
{
}

bool		DlManager::init()
{
  _DlLoader = new DlLoader;
  _browser = new DirectoryBrowser;
  return (true);
}

std::string						DlManager::getFolderPath() const
{
 return (_folderPath);
}

void							DlManager::setFolderPath(const std::string &path)
{
  this->getBrowser()->setPath(path);
  this->getBrowser()->refresh();
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
      _DlLoader->load(*it);
      tmp = _DlLoader->getInstance();
      if (tmp)
	_dl.push_back(std::pair<IEntity*, std::string>(tmp, tmp->getName()));
      else
	std::cout << "error on loading entity" << std::endl;
    }
  this->getBrowser()->clear();
  return (true);
}
