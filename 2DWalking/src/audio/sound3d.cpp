#include "sound3d.h"

Sound3d::Sound3d() : Sound()
{
	posX = 0.0; posY = 0.0; posZ = 0.0;

	alSourcei(this->id, AL_SOURCE_RELATIVE, AL_FALSE);
	alSourcef(this->id, AL_ROLLOFF_FACTOR, 1.2f);
	alSourcef(this->id, AL_REFERENCE_DISTANCE, 1);
	alSourcef(this->id, AL_MAX_DISTANCE, 20);
	alSource3f(this->id, AL_POSITION, this->posX, this->posY, this->posZ);
}

Sound3d::~Sound3d()
{

}

void Sound3d::setPosition(float x, float y, float z)
{
	alSource3f(this->id, AL_POSITION, x, y, z);
}

void Sound3d::setPosition(glm::vec3 position)
{
	alSource3f(this->id, AL_POSITION, position.x, position.y, position.z);
}

void Sound3d::setRolloffFactor(float factor)
{
	alSourcef(this->id, AL_ROLLOFF_FACTOR, factor);
}

void Sound3d::setReferenceDistance(float distance)
{
	alSourcef(this->id, AL_REFERENCE_DISTANCE, distance);
}

void Sound3d::setMaxDistance(float distance)
{
	alSourcef(this->id, AL_MAX_DISTANCE, distance);
}
