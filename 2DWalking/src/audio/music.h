#pragma once


#include <AL/alut.h>
#include <stdbool.h>
#include <corecrt_memory.h>
#include <map>
#include <string>

#include "soundpaths.h"
#include "../utilities/stb_vorbis.h"



#define BUFFER_SIZE 65536*8

class Music
{
private:
	stb_vorbis* stream;
	stb_vorbis_info info;

	ALuint id;
	ALuint buffers[2];
	ALenum format;

	size_t bufferSize;

	size_t totalSamplesLeft;

	bool shouldLoop;
	unsigned int startLoop;
	static const std::map<std::string, unsigned int> filesStartLoop;

public:
	Music();
	~Music();

	void init();
	void stop();

	bool open(const char* filename);
	bool musicStream(ALuint buffer);
	
	bool update();

	void setStartLoop(const char* filename);
	void setVolume(float gain);
	void setPitch(float pitch);
};

