#pragma once

#include "../../graphics/paints/sprite.h"


enum class CharaDirection {
	NONE = -1,
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};

class Chara : public Sprite
{
private:


public:

	Chara();
	~Chara();

	void move(float x, float y, CharaDirection direction = CharaDirection::NONE);
	void setDirection(CharaDirection direction);

	void setTexUVSpriteSheet(const int x, const int y);

};