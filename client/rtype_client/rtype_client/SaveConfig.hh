#pragma once

//
// saveConfig.hh for  in /home/gloulo_e/RTYPE
//
// Made by elyess gloulou
// Login   <gloulo_e@epitech.net>
//
// Started on  Tue Dec 13 01:21:17 2016 elyess gloulou
// Last update Thu Dec 15 18:48:03 2016 elyess gloulou
//

// #ifndef _SAVECONFIG_HH_
// # define _SAVECONFIG_HH_

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class saveConfig
{
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

private:
	std::string	_player;
	int	_general;
	int	_music;
	int	_sfx;
	int	_level;
	int	_shipModel;
};

// #endif	/*_SAVECONFIG_HH_*/
