#include "sound.h"

Sound::Sound()
{
	volume = 1.0; pitch = 1.0;
	posX = 0.0; posY = 0.0; posZ = 0.0;

	alGenSources(1, &this->id);
	alSourcef(this->id, AL_GAIN, this->volume);
	alSourcef(this->id, AL_PITCH, this->pitch);

	alSourcef(this->id, AL_ROLLOFF_FACTOR, 1.2f);
	alSourcef(this->id, AL_REFERENCE_DISTANCE, 1);
	alSourcef(this->id, AL_MAX_DISTANCE, 20);
	alSource3f(this->id, AL_POSITION, this->posX, this->posY, this->posZ);
}

Sound::~Sound()
{
	alDeleteSources(1, &this->id);
}

void Sound::play(ALuint buffer, float volume, float pitch)
{
	alSourcef(this->id, AL_GAIN, volume);
	alSourcef(this->id, AL_PITCH, pitch);
	alSourcei(this->id, AL_BUFFER, buffer);
	alSourcePlay(this->id);
}

void Sound::setPosition(float x, float y, float z)
{
	alSource3f(this->id, AL_POSITION, x, y, z);
}

void Sound::setPosition(glm::vec3 position)
{
	alSource3f(this->id, AL_POSITION, position.x, position.y, position.z);
}

void Sound::setVolume(float gain)
{
	alSourcef(this->id, AL_GAIN, gain);
}

void Sound::setPitch(float pitch)
{
	alSourcef(this->id, AL_PITCH, pitch);
}

void Sound::setRolloffFactor(float factor)
{
	alSourcef(this->id, AL_ROLLOFF_FACTOR, factor);
}

void Sound::setReferenceDistance(float distance)
{
	alSourcef(this->id, AL_REFERENCE_DISTANCE, distance);
}

void Sound::setMaxDistance(float distance)
{
	alSourcef(this->id, AL_MAX_DISTANCE, distance);
}



