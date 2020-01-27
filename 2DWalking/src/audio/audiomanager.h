#pragma once

#include <vector>
#include "../utilities/filemanager.h"
#include "../utilities/stb_vorbis.h"
#include "../utilities/mathmanager.h"
#include <AL/alut.h>
#include "music.h"
#include "soundpaths.h"
#include "sound.h"
#include "ambient.h"

class AudioManager
{
private:
	static std::map <std::string, ALuint> soundBuffers;
	static Music bgm;

public:
	
	AudioManager();
	~AudioManager();

	static ALuint loadWavSound(const char* filePath);
	static ALuint getBufferSound(const char* filePath);
	static void playSound(glm::vec3 position, const char* filePath, float volume = 1.0f, float pitch = 1.0f);
	static void playAmbient(glm::vec3 position, const char* filePath, float volume = 1.0f, float pitch = 1.0f);

	static void playMusic(const char* filePath);
	static void updateMusic();
	static void stopMusic();

	static void setListenerPosition(float x, float y, float z);
	static void setListenerPosition(glm::vec3 position);
};