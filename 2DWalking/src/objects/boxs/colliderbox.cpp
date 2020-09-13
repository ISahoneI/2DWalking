#include "colliderbox.h"

Colliderbox::Colliderbox() : Sprite(256, 144, 16.0f, 16.0f, glm::vec4(128, 0, 255, 128))
{
	setIsRender(false);
	setLevel(SpriteLevel::LEVEL4);
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


bool Colliderbox::collide(const Colliderbox* target)
{
	const glm::vec2 thisCenter = glm::vec2(getPositionX() + getWidth() * 0.5f, getPositionY() + getHeight() * 0.5f);
	const glm::vec2 targetCenter = glm::vec2(target->getPositionX() + target->getWidth() * 0.5f, target->getPositionY() + target->getHeight() * 0.5f);

	const float dx = thisCenter.x - targetCenter.x;
	const float dy = thisCenter.y - targetCenter.y;
	const float aw = (getWidth() + target->getWidth()) * 0.5f;
	const float ah = (getHeight() + target->getHeight()) * 0.5f;

	if (abs(dx) > aw || abs(dy) > ah)
		return false;

	if (abs(dx / target->getWidth()) > abs(dy / target->getHeight())) {
		if (dx < 0) setPositionX(target->getPositionX() - getWidth());
		else setPositionX(target->getPositionX() + target->getWidth());
	}
	else {
		if (dy < 0) setPositionY(target->getPositionY() - getHeight());
		else setPositionY(target->getPositionY() + target->getHeight());
	}

	return true;
}
