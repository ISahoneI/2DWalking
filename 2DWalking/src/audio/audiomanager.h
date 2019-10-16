#pragma once

#include <vector>
#include "../utilities/filemanager.h"
#include "../utilities/stb_vorbis.h"
#include <AL/alut.h>
#include "music.h"
#include "soundpaths.h"


class AudioManager
{
private:
	static std::vector<ALuint> buffers;
	static Music bgm;

public:
	
	AudioManager();
	~AudioManager();

	static ALuint loadWavSound(const char* filePath);
	static void playMusic(const char* filePath);
	static void updateMusic();
	static void stopMusic();

	static void setListenerPosition(float x, float y, float z);
};