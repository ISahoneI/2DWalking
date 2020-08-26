#include "colliderbox.h"

Colliderbox::Colliderbox() : Sprite(320, 160, 16.0f, 16.0f, glm::vec4(0.5f, 0, 1.0f, 0.5f))
{
	this->estVisible = true;
}

Colliderbox::~Colliderbox()
{
}

bool Colliderbox::isCollided(const Colliderbox* target)
{
	bool collisionX = this->getPositionX() + this->getWidth() >= target->getPositionX() &&
		target->getPositionX() + target->getWidth() >= this->getPositionX();

	bool collisionY = this->getPositionY() + this->getHeight() >= target->getPositionY() &&
		target->getPositionY() + target->getHeight() >= this->getPositionY();

	return collisionX && collisionY;
}

