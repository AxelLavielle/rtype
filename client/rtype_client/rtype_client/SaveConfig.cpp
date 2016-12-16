#include "SaveConfig.hh"

SaveConfig::SaveConfig()
{
  _player = "Player";
  _general = 250; // 50%
  _music = 250;
  _sfx = 250;
  _level = 1; // level 1
  _shipModel = 1; // ship 1
}

SaveConfig::SaveConfig(const int general, const int music,
		       const int sfx, const int level,
		       const int shipModel, const std::string &player)
{
  _player = player;
  _general = general;
  _music = music;
  _sfx = sfx;
  _level = level;
  _shipModel = shipModel;
}

SaveConfig::~SaveConfig()
{
}

void			SaveConfig::writeToFile()
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

void				SaveConfig::needleInHaystack(const std::string &haystack)
{
	// ifs to replace with a dual tab string tab and var adress tab on a single if
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

void				SaveConfig::readFromFile()
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

std::string	SaveConfig::getPlayer() const
{
  return (_player);
}

void		SaveConfig::setPlayer(const std::string &player)
{
  _player = player;
}

int		SaveConfig::getGeneral() const
{
  return (_general);
}

void		SaveConfig::setGeneral(const int general)
{
  _general = general;
}

int		SaveConfig::getMusic() const
{
  return (_music);
}

void		SaveConfig::setMusic(const int music)
{
  _music = music;
}

int		SaveConfig::getSfx() const
{
  return (_sfx);
}

void		SaveConfig::setSfx(const int sfx)
{
  _sfx = sfx;
}

int		SaveConfig::getLevel() const
{
  return (_level);
}

void		SaveConfig::setLevel(const int level)
{
  _level = level;
}

int		SaveConfig::getShipModel() const
{
  return (_shipModel);
}

void		SaveConfig::setShipModel(const int shipModel)
{
  _shipModel = shipModel;
}
