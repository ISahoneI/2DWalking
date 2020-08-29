#pragma once

#include "../../graphics/paints/sprite.h"
#include "../boxs/colliderbox.h"


enum class CharaDirection {
	NONE = -2,
	FIXE = -1,
	DOWN = 0,
	UP = 1,
	RIGHT = 2,
	LEFT = 3
};

class Chara : public Sprite
{
private:


public:
	Colliderbox* colliderbox;
	Colliderbox* Xcolliderbox;
	Colliderbox* Ycolliderbox;


	Chara();
	~Chara();

	void move(float x, float y, CharaDirection direction = CharaDirection::NONE);
	void setDirection(CharaDirection direction);

	void setTexUVSpriteSheet(const int x, const int y);

};