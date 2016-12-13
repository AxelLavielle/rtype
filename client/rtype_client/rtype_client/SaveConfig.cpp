//
// saveConfig.cpp for  in /home/gloulo_e/RTYPE
//
// Made by elyess gloulou
// Login   <gloulo_e@epitech.net>
//
// Started on  Tue Dec 13 01:21:20 2016 elyess gloulou
// Last update Tue Dec 13 03:59:52 2016 elyess gloulou
//

#include "saveConfig.hh"

void			saveConfig::writeToFile(void)
{
	std::fstream		fileStream;

	fileStream.open("menuConfig.xml",
		std::fstream::in |
		std::fstream::out |
		std::fstream::trunc);
	if (fileStream.is_open())
	{
		fileStream << "<Menu Config>\n";

		fileStream << "<General>" << general << "</General>\n";
		fileStream << "<Music>" << music << "</Music>\n";
		fileStream << "<SFX>" << sfx << "</SFX>\n";
		fileStream << "<Level>" << level << "</Level>\n";
		fileStream << "<Ship Model>" << shipModel << "</Ship Model>\n";

		fileStream << "</Menu Config>" << std::endl;
	}
	else
		std::cerr << "Error: Menu File Failed to Open!" << std::endl;

	fileStream.close();
}

void				saveConfig::needleInHaystack(std::string haystack)
{
	if (haystack.find("<General>") != std::string::npos
		&&  haystack.find("</General>") != std::string::npos)
	{
		std::cout << "</General>" << haystack.find("</General>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<General>") + 9,
			haystack.find("</General>")));
		ss >> general;
		std::cout << general << std::endl;
	}
	if (haystack.find("<Music>") != std::string::npos
		&&  haystack.find("</Music>") != std::string::npos)
	{
		std::cout << "</Music>" << haystack.find("</Music>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Music>") + 7,
			haystack.find("</Music>")));
		ss >> music;
		std::cout << music << std::endl;
	}
	if (haystack.find("<SFX>") != std::string::npos
		&&  haystack.find("</SFX>") != std::string::npos)
	{
		std::cout << "</SFX>" << haystack.find("</SFX>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<SFX>") + 5,
			haystack.find("</SFX>")));
		ss >> sfx;
		std::cout << sfx << std::endl;
	}
	if (haystack.find("<Level>") != std::string::npos
		&&  haystack.find("</Level>") != std::string::npos)
	{
		std::cout << "</Level>" << haystack.find("</Level>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Level>") + 7,
			haystack.find("</Level>")));
		ss >> level;
		std::cout << level << std::endl;
	}
	if (haystack.find("<Ship Model>") != std::string::npos
		&&  haystack.find("</Ship Model>") != std::string::npos)
	{
		std::cout << "</Ship Model>" << haystack.find("</Ship Model>") << std::endl;
		std::istringstream ss(haystack.substr(haystack.find("<Ship Model>") + 12,
			haystack.find("</Ship Model>")));
		ss >> shipModel;
		std::cout << shipModel << std::endl;
	}
}

void				saveConfig::readFromFile(void)
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

saveConfig::saveConfig(const int  general, const int  music,
	const int  sfx, const int  level, const int  shipModel)
{
	this->general = general;
	this->music = music;
	this->sfx = sfx;
	this->level = level;
	this->shipModel = shipModel;
}

saveConfig::~saveConfig() {}
