#pragma once

#include <dlfcn.h>
#include "IDlLoader.hpp"

class ADlLoader : public IDlLoader
{
protected:
	std::string		_dlPath;
	void		       	*_dlHandle;
public:
	ADlLoader();
	virtual ~ADlLoader();

	virtual void	*getHandle();
	virtual IEntity	*getInstance() = 0;
	virtual bool	load(const std::string &) = 0;
	virtual bool	refresh() = 0;
};
