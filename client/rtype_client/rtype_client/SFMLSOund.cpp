#include "SFMLSound.hh"



SFMLSound::SFMLSound()
{
}


SFMLSound::~SFMLSound()
{
}

sf::Music	*SFMLSound::getMusic(const std::string & path) const
{
	std::map<sf::Music*, std::string>::const_iterator	it;

	it = _music.begin();
	while (it != _music.end())
	{
		if (it->second == path)
			return (it->first);
		++it;
	}
	return (NULL);
}


sf::Sound	*SFMLSound::getSound(const std::string & path) const
{
	std::map<sf::Sound*, std::string>::const_iterator	it;

	it = _sound.begin();
	while (it != _sound.end())
	{
		if (it->second == path)
			return (it->first);
		++it;
	}
	return (NULL);
}

bool SFMLSound::play(const Sound & sound)
{
	//if (sound.isMusic())
	//{
	//	sf::Sound *sd;
	//	sf::SoundBuffer		buffer;
	//	if (!(sd = getSound(sound.getFilePath())))
	//	{
	//		if (!buffer.loadFromFile(sound.getFilePath()))
	//			return (false);
	//		sd->setBuffer(buffer);
	//		sd->play();
	//		_sound.insert(std::pair<sf::Sound*, std::string>(sd, sound.getFilePath()));
	//	}
	//}
	//else
	//{
	//	sf::Music	*music;
	//	sf::SoundBuffer		buffer;
	//	if (!(music = getMusic(sound.getFilePath())))
	//	{
	//		if (!buffer.loadFromFile(sound.getFilePath()))
	//			return (false);
	//		sd->setBuffer(buffer);
	//		sd->play();
	//		_sound.insert(std::pair<sf::Sound*, std::string>(sd, sound.getFilePath()));
	//	}
	//}
	return (true);
}

bool SFMLSound::stop(const Sound & sound)
{
	//Not implemented
	return (true);
}

bool SFMLSound::pause(const Sound & sound)
{
	//Not implemented
	return (true);
}
