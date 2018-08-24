#include "source.h"

Source::Source()
{
	alGenSources(1, &this->id);
	alSourcef(this->id, AL_GAIN, 1);
	alSourcef(this->id, AL_PITCH, 1);
	alSource3f(this->id, AL_POSITION, 0, 0, 0);
}

Source::~Source()
{
	alDeleteSources(1, &this->id);
}

void Source::play(ALuint buffer)
{
	alSourcei(this->id, AL_BUFFER, buffer);
	alSourcePlay(this->id);
}