#pragma once

#include <vector>
#include "../utilities/filemanager.h"
#include <AL/alut.h>

#define DW_MUSIC_1 "res/sound/music/music1.ogg"
#define DW_SOUND_1 "res/sound/se/test.wav"

class AudioManager
{
private:
	std::vector<ALuint> buffers;

public:
	AudioManager();
	~AudioManager();

	ALuint loadSound(const char* filePath);

private:
	void init();
};