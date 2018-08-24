#include "audiomanager.h"

AudioManager::AudioManager()
{
	init();
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
	this->buffers.push_back(buffer);

	return buffer;
}

void AudioManager::init()
{
	alutInit(NULL, NULL);
}