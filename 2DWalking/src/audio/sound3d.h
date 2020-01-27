#pragma once

#include "sound.h"

class Sound3d : public Sound {
private:
	float posX, posY, posZ;

public:
	Sound3d();
	~Sound3d();

	void setPosition(float x, float y, float z);
	void setPosition(glm::vec3 position);

	void setRolloffFactor(float factor);
	void setReferenceDistance(float distance);
	void setMaxDistance(float distance);
};