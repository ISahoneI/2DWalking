#pragma once
#include "../../graphics/paints/sprite.h"


class Colliderbox : public Sprite
{
private:
	bool estVisible;

public:
	Colliderbox();
	~Colliderbox();

	bool isCollided(const Colliderbox* target);

};