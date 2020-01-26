#include "audiomanager.h"

std::map <std::string, ALuint> AudioManager::soundBuffers;
Music AudioManager::bgm;

AudioManager::AudioManager()
{
	alutInit(NULL, NULL);
	soundBuffers = {
		{ DW_SOUND_1, AudioManager::loadWavSound(DW_SOUND_1) },
		{ DW_SOUND_2, AudioManager::loadWavSound(DW_SOUND_2) }
	};

	alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
}

AudioManager::~AudioManager()
{
	for (auto it = soundBuffers.begin(); it != soundBuffers.end(); ++it) {
		alDeleteBuffers(1, &it->second);
	}

	//for(ALuint buffer : this->buffers)
	//	alDeleteBuffers(1, &buffer);
}

ALuint AudioManager::loadWavSound(const char* filePath)
{
	ALuint buffer = alutCreateBufferFromFile(filePath);
	if (buffer == AL_NONE)
	{
		std::cout << "Failed to load the sound : " << filePath << " !" << std::endl;
		return NULL;
	}
	//buffers.push_back(buffer);

	return buffer;
}

ALuint AudioManager::getBufferSound(const char* filePath)
{
	return soundBuffers.at(filePath);
}

void AudioManager::playSound(glm::vec3 position, const char* filePath, float volume, float pitch)
{
	ALuint buffer = getBufferSound(filePath);
	Sound* sound = new Sound();
	sound->setPosition(position);
	sound->play(buffer, volume, pitch);
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

void AudioManager::setListenerPosition(glm::vec3 position)
{
	alListener3f(AL_POSITION, position.x, position.y, position.z);
}


