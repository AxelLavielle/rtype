#pragma once

//
// saveConfig.hh for  in /home/gloulo_e/RTYPE
//
// Made by elyess gloulou
// Login   <gloulo_e@epitech.net>
//
// Started on  Tue Dec 13 01:21:17 2016 elyess gloulou
// Last update Wed Dec 14 22:07:09 2016 elyess gloulou
//

#ifndef _SAVECONFIG_HH_
# define _SAVECONFIG_HH_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class saveConfig
{
	std::string	player;
	int	general;
	int	music;
	int	sfx;
	int	level;
	int	shipModel;

public:
	void	writeToFile(void);
	void	readFromFile(void);
	void  needleInHaystack(std::string);

  //getters
  std::string	getPlayer();
  int		getGeneral();
  int		getMusic();
  int		getSfx();
  int		getLevel();
  int		getShipModel();
  saveConfig(int, int, int, int, int);
  ~saveConfig();

};

#endif	/*_SAVECONFIG_HH_*/
