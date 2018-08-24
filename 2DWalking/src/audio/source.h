#pragma once

#include <AL/alut.h>

class Source {
private:
	ALuint id;
	float posX, posY, posZ;
	float volume;
	float pitch;

public:
	Source();
	~Source();

	void setPosition(float x, float y, float z);

	void play(ALuint buffer);
	void setVolume(float volume);
	void setPitch(float pitch);
};