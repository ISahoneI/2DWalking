#pragma once

#include "../../graphics/paints/sprite.h"
#include "../boxs/colliderbox.h"

enum class CharaAnimeState {
	IDLE = 0,
	WALKING = 1,
	RUNNING = 2
};

enum class CharaDirection {
	NONE = -2,
	FIXE = -1,
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
	UP_RIGHT = 4,
	UP_LEFT = 5,
	DOWN_RIGHT = 6,
	DOWN_LEFT = 7
};

class Chara : public Sprite
{
private:
	Colliderbox* colliderbox;
	CharaDirection direction;
	CharaAnimeState animeState;
	int animeFrame = 1; int walkAnimeFoot = 1;
	int nbFrame = 3;

	float speed;
	float animationSpeed = 0.12f; //120 ms
	float deltaTimeCount = 0.0f;

public:

	Chara();
	~Chara();

	void move(float x, float y, CharaDirection direction = CharaDirection::NONE);
	void setDirection(CharaDirection direction);
	void animation(double deltaTime);
	void setTexUVSpriteSheet(const int x, const int y);


	CharaDirection getDirection() { return direction; }

	CharaAnimeState getAnimeState() { return animeState; }
	void setAnimeState(CharaAnimeState animeState) { this->animeState = animeState; }

	const float getSpeed() { return speed; }
	void setSpeed(float speed) { this->speed = speed; }

	const float getAnimationSpeed() { return animationSpeed; }
	void setAnimationSpeed(float animationSpeed) { this->animationSpeed = animationSpeed; }

	Colliderbox* getColliderbox() { return colliderbox; }
	bool collide(const Colliderbox* target);

	void update(double deltaTime);

private:
	void initColliderBox();
};