//
// saveConfig.cpp for  in /home/gloulo_e/RTYPE
//
// Made by elyess gloulou
// Login   <gloulo_e@epitech.net>
//
// Started on  Tue Dec 13 01:21:20 2016 elyess gloulou
// Last update Thu Dec 15 18:43:36 2016 elyess gloulou
//

#include "saveConfig.hh"

void			saveConfig::writeToFile()
{
	std::fstream		fileStream;

	fileStream.open("menuConfig.xml",
		std::fstream::in |
		std::fstream::out |
		std::fstream::trunc);
	if (fileStream.is_open())
	{
		fileStream << "<Menu Config>\n";

		fileStream << "<Player>" << _player << "</Player>\n";
		fileStream << "<General>" << _general << "</General>\n";
		fileStream << "<Music>" << _music << "</Music>\n";
		fileStream << "<SFX>" << _sfx << "</SFX>\n";
		fileStream << "<Level>" << _level << "</Level>\n";
		fileStream << "<Ship Model>" << _shipModel << "</Ship Model>\n";

		fileStream << "</Menu Config>" << std::endl;
	}
	else
		std::cerr << "Error: Menu File Failed to Open!" << std::endl;

	fileStream.close();
}

void				saveConfig::needleInHaystack(std::string haystack)
{ // ifs to replace with a dual tab string tab and var adress tab on a single if
	if (haystack.find("<Player>") != std::string::npos
		&&  haystack.find("</Player>") != std::string::npos)
	{
		std::cout << "</Player>" << haystack.find("</Player>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Player>") + 8,
			haystack.find("</Player>")));
		ss >> _player;
		// std::cout << player << std::endl;
	}
	if (haystack.find("<General>") != std::string::npos
		&&  haystack.find("</General>") != std::string::npos)
	{
		std::cout << "</General>" << haystack.find("</General>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<General>") + 9,
			haystack.find("</General>")));
		ss >> _general;
		// std::cout << general << std::endl;
	}
	if (haystack.find("<Music>") != std::string::npos
		&&  haystack.find("</Music>") != std::string::npos)
	{
		std::cout << "</Music>" << haystack.find("</Music>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Music>") + 7,
			haystack.find("</Music>")));
		ss >> _music;
		// std::cout << music << std::endl;
	}
	if (haystack.find("<SFX>") != std::string::npos
		&&  haystack.find("</SFX>") != std::string::npos)
	{
		std::cout << "</SFX>" << haystack.find("</SFX>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<SFX>") + 5,
			haystack.find("</SFX>")));
		ss >> _sfx;
		// std::cout << sfx << std::endl;
	}
	if (haystack.find("<Level>") != std::string::npos
		&&  haystack.find("</Level>") != std::string::npos)
	{
		std::cout << "</Level>" << haystack.find("</Level>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Level>") + 7,
			haystack.find("</Level>")));
		ss >> _level;
		// std::cout << level << std::endl;
	}
	if (haystack.find("<Ship Model>") != std::string::npos
		&&  haystack.find("</Ship Model>") != std::string::npos)
	{
		std::cout << "</Ship Model>" << haystack.find("</Ship Model>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Ship Model>") + 12,
			haystack.find("</Ship Model>")));
		ss >> _shipModel;
		// std::cout << shipModel << std::endl;
	}
}

void				saveConfig::readFromFile()
{
	std::fstream			fileStream;

	fileStream.open("menuConfig.xml",
		std::fstream::in |
		std::fstream::binary |
		std::fstream::out);

	if (fileStream.is_open())
	{
		std::string line;

		while (getline(fileStream, line))
			needleInHaystack(line);
	}
	else
		std::cerr << "Error: Menu File Failed to Open!1" << std::endl;
}

std::string	saveConfig::getPlayer()
{
  return _player;
}

int		saveConfig::getGeneral()
{
  return _general;
}

int		saveConfig::getMusic()
{
  return _music;
}

int		saveConfig::getSfx()
{
  return _sfx;
}

int		saveConfig::getLevel()
{
  return _level;
}

int		saveConfig::getShipModel()
{
  return _shipModel;
}

saveConfig::saveConfig()
{
  _player = "Player";
  _general = 250; // 50%
  _music = 250;
  _sfx = 250;
  _level = 1; // level 1
  _shipModel = 1; // ship 1
}

saveConfig::saveConfig(const int  general, const int  music,
		       const int  sfx, const int  level,
		       const int shipModel, const std::string player)
{
  _player = player;
  _general = general;
  _music = music;
  _sfx = sfx;
  _level = level;
  _shipModel = shipModel;
}

saveConfig::~saveConfig() {}
