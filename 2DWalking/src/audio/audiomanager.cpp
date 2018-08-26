#include "audiomanager.h"

std::vector<ALuint> AudioManager::buffers;

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

ALuint AudioManager::loadSound(const char* filePath)
{
	ALuint buffer = buffer = alutCreateBufferFromFile(filePath);
	if (buffer == AL_NONE)
	{
		std::cout << "Failed to load the sound : " << filePath << " !" << std::endl;
		return NULL;
	}
	buffers.push_back(buffer);

	return buffer;
}

void AudioManager::setListenerPosition(float x, float y, float z)
{
	alListener3f(AL_POSITION, x, y, z);
}