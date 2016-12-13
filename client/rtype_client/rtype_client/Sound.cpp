#include "Sound.hh"



Sound::Sound()
{
	_duration = 0;
	_filePath = "";
}

Sound::Sound(const int duration, const std::string & path)
{
	_duration = duration;
	_filePath = path;
}


Sound::~Sound()
{
}

void Sound::setDuration(const int duration)
{
	_duration = duration;
}

void Sound::setFilePath(const std::string & path)
{
	_filePath = path;
}

int Sound::getDuration() const
{
	return (_duration);
}

std::string Sound::getFilePath() const
{
	return (_filePath);
}

void Sound::setMusic(const bool flag)
{
	_isMusic = flag;
}

bool Sound::isMusic() const
{
	return (_isMusic);
}
