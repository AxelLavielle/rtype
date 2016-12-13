#pragma once

//
// saveConfig.hh for  in /home/gloulo_e/RTYPE
//
// Made by elyess gloulou
// Login   <gloulo_e@epitech.net>
//
// Started on  Tue Dec 13 01:21:17 2016 elyess gloulou
// Last update Tue Dec 13 03:54:33 2016 elyess gloulou
//

#ifndef _SAVECONFIG_HH_
# define _SAVECONFIG_HH_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class saveConfig
{
	int	general;
	int	music;
	int	sfx;
	int	level;
	int	shipModel;

public:
	void	writeToFile(void);
	void	readFromFile(void);
	void  needleInHaystack(std::string);

	saveConfig(int, int, int, int, int);
	~saveConfig();

};

#endif	/*_SAVECONFIG_HH_*/
