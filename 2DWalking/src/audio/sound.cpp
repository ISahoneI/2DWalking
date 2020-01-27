#include "sound.h"

Sound::Sound()
{
	volume = 1.0; pitch = 1.0;

	alGenSources(1, &this->id);
	alSourcef(this->id, AL_GAIN, this->volume);
	alSourcef(this->id, AL_PITCH, this->pitch);
	alSourcei(this->id, AL_SOURCE_RELATIVE, AL_TRUE);
	alSource3f(this->id, AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(this->id, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
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

void Sound::setVolume(float gain)
{
	alSourcef(this->id, AL_GAIN, gain);
}

void Sound::setPitch(float pitch)
{
	alSourcef(this->id, AL_PITCH, pitch);
}

