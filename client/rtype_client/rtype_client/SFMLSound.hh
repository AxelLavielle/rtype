#pragma once

#include <map>
#include <SFML/Audio.hpp>
#include "ASoundManager.hh"

class SFMLSound :
	public ASoundManager
{
public:
	SFMLSound();
	virtual ~SFMLSound();
	virtual bool init();
	virtual bool play(const Sound & sound);
	virtual bool stop(const Sound & sound);
	virtual bool pause(const Sound & sound);
	virtual bool setVolume(const int);
	virtual bool setMusicVolume(const int);
	virtual bool setSoundVolume(const int);
	virtual void stopAll();
private:
	std::map<sf::Sound*, std::string >		_sound;
	std::map<sf::Music*, std::string >		_music;
	std::vector<sf::SoundBuffer*>			_buffer;

	sf::Sound *getSound(const std::string & path) const;
	sf::Music *getMusic(const std::string & path) const;
};

