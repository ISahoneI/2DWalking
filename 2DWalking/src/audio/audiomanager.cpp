#include "audiomanager.h"

std::vector<ALuint> AudioManager::buffers;
Music AudioManager::bgm;

AudioManager::AudioManager()
{
	alutInit(NULL, NULL);
	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

AudioManager::~AudioManager()
{
	for(ALuint buffer : this->buffers)
		alDeleteBuffers(1, &buffer);
}

ALuint AudioManager::loadWavSound(const char* filePath)
{
	ALuint buffer = alutCreateBufferFromFile(filePath);
	if (buffer == AL_NONE)
	{
		std::cout << "Failed to load the sound : " << filePath << " !" << std::endl;
		return NULL;
	}
	buffers.push_back(buffer);

	return buffer;
}


void AudioManager::playMusic(const char* filePath)
{
	bgm.stop();
	bgm.init();
	bgm.open(filePath);
}

void AudioManager::updateMusic()
{
	bgm.update();
}

void AudioManager::stopMusic()
{
	bgm.stop();
}

void AudioManager::setListenerPosition(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
}
