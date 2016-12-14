#include "SFMLSound.hh"

SFMLSound::SFMLSound()
{
}

SFMLSound::~SFMLSound()
{
	std::map<sf::Music*, std::string>::iterator	it;
	std::map<sf::Sound*, std::string>::iterator	it2;
	std::vector<sf::SoundBuffer* >::iterator		it3;

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
	it3 = _buffer.begin();
	while (it3 != _buffer.end())
	{
		delete (*it3);
		++it3;
	}
	_buffer.clear();
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
	if (!sound.isMusic())
	{
		sf::Sound *sd;
		sf::SoundBuffer		*buffer;
		if (!(sd = getSound(sound.getFilePath())))
		{
			buffer = new sf::SoundBuffer();
			if (!buffer->loadFromFile(sound.getFilePath()))
				return (false);
			sd = new sf::Sound();
			sd->setBuffer(*buffer);
			sd->setLoop(sound.isLoop());
			sd->play();
			_sound.insert(std::pair<sf::Sound*, std::string>(sd, sound.getFilePath()));
			_buffer.push_back(buffer);
		}
		else
			sd->play();
	}
	else
	{
		sf::Music	*music;
		if (!(music = getMusic(sound.getFilePath())))
		{
			music = new sf::Music();
			if (!music->openFromFile(sound.getFilePath()))
				return (false);
			music->setLoop(sound.isLoop());
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
	if (sound.isMusic())
	{
		sf::Music	*music;
		if ((music = getMusic(sound.getFilePath())))
			music->stop();
	}
	else
	{
		sf::Sound	*sd;
		if ((sd = getSound(sound.getFilePath())))
			sd->stop();
	}
	return (true);
}

bool SFMLSound::pause(const Sound & sound)
{
	if (sound.isMusic())
	{
		sf::Music	*music;
		if ((music = getMusic(sound.getFilePath())))
			music->pause();
	}
	else
	{
		sf::Sound	*sd;
		if ((sd = getSound(sound.getFilePath())))
			sd->pause();
	}
	return (true);
}

bool SFMLSound::setVolume(const int volume)
{
	setMusicVolume(volume);
	setSoundVolume(volume);
	return (true);;
}

bool SFMLSound::setMusicVolume(const int volume)
{
	std::map<sf::Music*, std::string>::iterator	it;

	it = _music.begin();
	while (it != _music.end())
	{
		it->first->setVolume(volume);
		++it;
	}
	return (true);
}

bool SFMLSound::setSoundVolume(const int volume)
{
	std::map<sf::Sound*, std::string>::iterator	it;

	it = _sound.begin();
	while (it != _sound.end())
	{
		it->first->setVolume(volume);
		++it;
	}
	return (true);
}

void SFMLSound::stopAll()
{
	std::map<sf::Music*, std::string>::iterator	it;
	std::map<sf::Sound*, std::string>::iterator	it2;

	it = _music.begin();
	while (it != _music.end())
	{
		it->first->stop();
		++it;
	}
	it2 = _sound.begin();
	while (it2 != _sound.end())
	{
		it2->first->stop();
		++it2;
	}
}
