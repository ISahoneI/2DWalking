#pragma once

#include <AL/alut.h>
#include "../utilities/mathmanager.h"

class Sound {
protected:
	ALuint id;
	float volume;
	float pitch;

public:
	Sound();
	~Sound();

	void play(ALuint buffer, float volume = 1.0f, float pitch = 1.0f);

	void setVolume(float gain);
	void setPitch(float pitch);
};