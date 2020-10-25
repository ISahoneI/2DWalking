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


	bool isOverlap(const Colliderbox* target);
	bool collide(const Colliderbox* target);

	const bool getIsCollidable() const { return isCollidable; }
	void setIsCollidable(bool isCollidable) { this->isCollidable = isCollidable; }
};
