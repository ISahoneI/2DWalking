#pragma once

#include <AL/alut.h>


class Sound {
private:
	ALuint id;
	float posX, posY, posZ;
	float volume;
	float pitch;

public:
	Sound();
	~Sound();

	void play(ALuint buffer, float volume = 1.0f, float pitch = 1.0f);

	void setPosition(float x, float y, float z);

	void setVolume(float gain);
	void setPitch(float pitch);

	void setRolloffFactor(float factor);
	void setReferenceDistance(float distance);
	void setMaxDistance(float distance);
};