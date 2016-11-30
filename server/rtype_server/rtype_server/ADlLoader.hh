#pragma once

#include <dlfcn.h>
#include "IDlLoader.hpp"

class ADlLoader : public IDlLoader
{
public:
	ADlLoader();
	virtual			~ADlLoader();
	virtual void		*getHandle();
	virtual bool		closeHandle();
private:
	std::string		_dlPath;
	void		       	*_dlHandle;
};
