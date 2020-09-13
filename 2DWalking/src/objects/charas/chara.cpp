#include "chara.h"

Chara::Chara() : Sprite(360, 120, 32, 40, new Texture("res/textures/spritesheet/Heros_Yzao.png"), glm::vec4(255, 255, 255, 255))
{
	setAnimeState(CharaAnimeState::IDLE);
	setLevel(SpriteLevel::LEVEL1);
	setSpeed(100.0f);
	setTexUVSpriteSheet(1, 2);
	colliderbox = new Colliderbox();
	initColliderBox();
}

Chara::~Chara()
{
}

void Chara::move(float x, float y, CharaDirection direction)
{
	float distX = getPositionX() - x;
	float distY = getPositionY() - y;

	if (distX != 0.0f || distY != 0.0f) {
		setAnimeState(CharaAnimeState::WALKING);
		if (direction != CharaDirection::FIXE) {
			if (direction == CharaDirection::NONE) {
				if ((distY * distY) > (distX * distX)) {
					if (distY > 0.0f)
						setDirection(CharaDirection::DOWN);
					else
						setDirection(CharaDirection::UP);
				}
				else {
					if (distX > 0.0f)
						setDirection(CharaDirection::LEFT);
					else
						setDirection(CharaDirection::RIGHT);
				}
			}
			else {
				setDirection(direction);
			}
		}

		if (distX != 0.0f) {
			setPositionX(x);
			colliderbox->setPositionX(x + 9.0f);
		}
		if (distY != 0.0f) {
			setPositionY(y);
			colliderbox->setPositionY(y);
		}

	}
	else {
		setAnimeState(CharaAnimeState::IDLE);
		//deltaTimeCount = 0.0f;
	}
}


void Chara::setDirection(CharaDirection direction)
{
	this->direction = direction;
	setTexUVSpriteSheet(animeFrame, (int)direction);
}

void Chara::animation(double deltaTime)
{
	deltaTimeCount += (float)deltaTime;
	if (animeState == CharaAnimeState::IDLE) {
		animeFrame = 1;
	}
	else if (animeState == CharaAnimeState::WALKING) {
		if (deltaTimeCount >= animationSpeed) {
			deltaTimeCount = 0.0f;
			animeFrame = (animeFrame + walkAnimeFoot) % nbFrame;
			if (animeFrame == 2 && walkAnimeFoot == 1) {
				walkAnimeFoot = -1;
			}
			if (animeFrame == 0 && walkAnimeFoot == -1) {
				walkAnimeFoot = 1;
			}
		}
	}
	setTexUVSpriteSheet(animeFrame, (int)direction);
}

void Chara::setTexUVSpriteSheet(const int x, const int y)
{
	uv.clear();
	const float tx = (float)(x * getWidth()) / (float)texture->getWidth();
	const float ty = (float)(y * getHeight()) / (float)texture->getHeight();
	const float w = (float)getWidth() / (float)texture->getWidth();
	const float h = (float)getHeight() / (float)texture->getHeight();
	uv.push_back(glm::vec2(tx, h + ty));
	uv.push_back(glm::vec2(tx, ty));
	uv.push_back(glm::vec2(w + tx, ty));
	uv.push_back(glm::vec2(w + tx, h + ty));
}

bool Chara::collide(const Colliderbox* target)
{
	bool collideTest = colliderbox->collide(target);
	if (collideTest)
	{
		setPositionX(colliderbox->getPositionX() - 9.0f);
		setPositionY(colliderbox->getPositionY());
	}
	return collideTest;
}

void Chara::update(double deltaTime)
{
	animation(deltaTime);
}

void Chara::initColliderBox()
{
	colliderbox->setSize(14, 12);
	colliderbox->setColor(255, 0, 0, 128);
	colliderbox->setPosition(getPositionX() + 9.0f, getPositionY());
}

