#include "colliderbox.h"

Colliderbox::Colliderbox() : Sprite(4, 4, 1, 1, glm::vec4(0.5f, 0, 1.0f, 0.5f))
{
	this->estVisible = true;
}

Colliderbox::~Colliderbox()
{
}
