#include "source.h"

Source::Source()
{
	alGenSources(1, &this->id);
	alSourcef(this->id, AL_GAIN, 1);
	alSourcef(this->id, AL_PITCH, 1);
	alSourcef(this->id, AL_ROLLOFF_FACTOR, 1.2f);
	alSourcef(this->id, AL_REFERENCE_DISTANCE, 1);
	alSourcef(this->id, AL_MAX_DISTANCE, 20);
	alSource3f(this->id, AL_POSITION, 0, 0, 0);
}

Source::~Source()
{
	alDeleteSources(1, &this->id);
}

void Source::play(ALuint buffer, float volume, float pitch)
{
	alSourcef(this->id, AL_GAIN, volume);
	alSourcef(this->id, AL_PITCH, pitch);
	alSourcei(this->id, AL_BUFFER, buffer);
	alSourcePlay(this->id);
}

void Source::setPosition(float x, float y, float z)
{
	alSource3f(this->id, AL_POSITION, x, y, z);
}

void Source::setVolume(float gain)
{
	alSourcef(this->id, AL_GAIN, gain);
}

void Source::setPitch(float pitch)
{
	alSourcef(this->id, AL_PITCH, pitch);
}

void Source::setRolloffFactor(float factor)
{
	alSourcef(this->id, AL_ROLLOFF_FACTOR, factor);
}

void Source::setReferenceDistance(float distance)
{
	alSourcef(this->id, AL_REFERENCE_DISTANCE, distance);
}

void Source::setMaxDistance(float distance)
{
	alSourcef(this->id, AL_MAX_DISTANCE, distance);
}


