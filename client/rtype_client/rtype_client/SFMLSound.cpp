#include "SFMLSound.hh"



SFMLSound::SFMLSound()
{
}


SFMLSound::~SFMLSound()
{
	std::map<sf::Music*, std::string>::const_iterator	it;
	std::map<sf::Sound*, std::string>::const_iterator	it2;

	it = _music.begin();
	while (it != _music.end())
	{
		delete (it->first);
		++it;
	}
	_music.clear();
	it2 = _sound.begin();
	while (it2 != _sound.end())
	{
		delete (it2->first);
		++it2;
	}
	_sound.clear();
}

bool SFMLSound::init()
{
	return (true);
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
	if (sound.isMusic())
	{
		sf::Sound *sd;
		sf::SoundBuffer		buffer;
		if (!(sd = getSound(sound.getFilePath())))
		{
			if (!buffer.loadFromFile(sound.getFilePath()))
				return (false);
			sd = new sf::Sound();
			sd->setBuffer(buffer);
			sd->play();
			_sound.insert(std::pair<sf::Sound*, std::string>(sd, sound.getFilePath()));
		}
		else
			sd->play();
	}
	else
	{
		sf::Music	*music;

		if (!(music = getMusic(sound.getFilePath())))
		{
			if (!music->openFromFile(sound.getFilePath()))
				return (false);
			music = new sf::Music();
			music->play();
			_music.insert(std::pair<sf::Music*, std::string>(music, sound.getFilePath()));
		}
		else
			music->play();
	}
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
