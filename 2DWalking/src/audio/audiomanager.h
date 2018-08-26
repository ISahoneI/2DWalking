#pragma once

#include <vector>
#include "../utilities/filemanager.h"
#include <AL/alut.h>

#define DW_MUSIC_1 "res/sound/music/music1.ogg"
#define DW_SOUND_1 "res/sound/se/Skyle_Hit1.wav"

class AudioManager
{
private:
	static std::vector<ALuint> buffers;

public:
	AudioManager();
	~AudioManager();

	static ALuint loadSound(const char* filePath);
	static void setListenerPosition(float x, float y, float z);
};