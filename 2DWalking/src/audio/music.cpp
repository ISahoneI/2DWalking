#include "music.h"

const std::map<std::string, unsigned int> Music::filesStartLoop = {
   {DW_MUSIC_1, 1289033},
   {DW_MUSIC_2, 0},
   {DW_MUSIC_3, 1008800},
   {DW_MUSIC_4, 574938}
};

Music::Music()
{
	init();
}

Music::~Music()
{
	stop();
}

void Music::init()
{
	memset(this, 0, sizeof(Music));
	alGenSources(1, &this->id);
	alGenBuffers(2, this->buffers);
	this->bufferSize = 4096 * 8;
	this->shouldLoop = true;
	this->startLoop = 0;
}

void Music::stop()
{
	alDeleteSources(1, &this->id);
	alDeleteBuffers(2, this->buffers);
	stb_vorbis_close(this->stream);
	memset(this, 0, sizeof(Music));
}

bool Music::open(const char* filename)
{
	this->stream = stb_vorbis_open_filename((char*)filename, NULL, NULL);
	if (!this->stream) return false;
	setStartLoop(filename);
	this->info = stb_vorbis_get_info(this->stream);
	if (this->info.channels == 2)
		this->format = AL_FORMAT_STEREO16;
	else
		this->format = AL_FORMAT_MONO16;

	if (!musicStream(this->buffers[0])) return false;
	if (!musicStream(this->buffers[1])) return false;

	alSourceQueueBuffers(this->id, 2, this->buffers);
	alSourcePlay(this->id);

	this->totalSamplesLeft = stb_vorbis_stream_length_in_samples(this->stream) * this->info.channels;

	return true;
}

bool Music::musicStream(ALuint buffer)
{
	ALshort pcm[BUFFER_SIZE];
	int  size = 0;
	int  result = 0;

	while (size < BUFFER_SIZE) {
		result = stb_vorbis_get_samples_short_interleaved(this->stream, this->info.channels, pcm + size, BUFFER_SIZE - size);
		if (result > 0) size += result * this->info.channels;
		else break;
	}

	if (size == 0) return false;

	alBufferData(buffer, this->format, pcm, size * sizeof(ALshort), this->info.sample_rate);
	this->totalSamplesLeft -= size;

	return true;
}

bool Music::update()
{
	ALint processed = 0;

	alGetSourcei(this->id, AL_BUFFERS_PROCESSED, &processed);

	while (processed--) {
		ALuint buffer = 0;

		alSourceUnqueueBuffers(this->id, 1, &buffer);

		if (!musicStream(buffer)) {
			bool shouldExit = true;

			if (this->shouldLoop) {
				stb_vorbis_seek(this->stream, this->startLoop);
				this->totalSamplesLeft = stb_vorbis_stream_length_in_samples(this->stream) * this->info.channels;
				shouldExit = !musicStream(buffer);
			}

			if (shouldExit) return false;
		}
		alSourceQueueBuffers(this->id, 1, &buffer);
	}

	return true;
}

void Music::setStartLoop(const char* filename)
{
	this->startLoop = filesStartLoop.at(filename);
}

void Music::setVolume(float gain)
{
	alSourcef(this->id, AL_GAIN, gain);
}

void Music::setPitch(float pitch)
{
	alSourcef(this->id, AL_PITCH, pitch);
}

