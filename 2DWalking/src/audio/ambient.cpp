#include "ambient.h"


Ambient::Ambient() : Sound()
{
	
}

Ambient::~Ambient()
{

}

void Ambient::play(ALuint buffer, float volume, float pitch)
{
	alSourcei(id, AL_LOOPING, 1);
	Sound::play(buffer, volume, pitch);
}
