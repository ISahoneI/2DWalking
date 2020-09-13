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

public:
	Colliderbox();
	~Colliderbox();


	bool isCollided(const Colliderbox* target);
	bool collide(const Colliderbox* target);


};
