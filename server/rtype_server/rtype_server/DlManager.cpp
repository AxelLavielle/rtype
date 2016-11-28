#include "DlManager.hh"

DlManager::DlManager() : _DlLoader(NULL)
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
  _folderPath = path;
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
