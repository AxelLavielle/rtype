#include "DlManager.hh"
#include "UDlLoader.hh"
#include "UDirectoryBrowser.hh"

DlManager::DlManager() : _DlLoader(new UDlLoader), _browser(new UDirectoryBrowser)
{
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
