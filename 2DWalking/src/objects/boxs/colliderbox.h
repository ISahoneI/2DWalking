#pragma once
#include "../../graphics/paints/sprite.h"

enum class CollideDirection {
	OTHER = -2,
	NONE = -1,
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};


class Colliderbox : public Sprite
{
private:
	bool isCollidable;

public:
	Colliderbox(float x, float y, float width, float height);
	~Colliderbox();


	bool isCollided(const Colliderbox* target);
	bool collide(const Colliderbox* target);

	bool getIsCollidable() { return isCollidable; }
	void setIsCollidable(bool isCollidable) { this->isCollidable = isCollidable; }
};
