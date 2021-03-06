#include "chara.h"


Chara::Chara(Texture* spritesheet) : Sprite(360, 820, 32, 40, spritesheet, glm::vec4(255, 255, 255, 255))
{
	setAnimeState(CharaAnimeState::IDLE);
	setLevel(SpriteLevel::LEVEL1);
	setSpeed(100.0f);
	setTexUVSpriteSheet(1, 2);
	initColliderBox();
	initSounds3d();
}

Chara::~Chara()
{
	delete colliderbox;
	for (size_t i = 0; i < sounds3d.size(); i++) {
		delete sounds3d[i];
	}
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
			colliderbox->setPositionX(x + 10.0f);
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
		setPositionX(colliderbox->getPositionX() - 10.0f);
		setPositionY(colliderbox->getPositionY());
	}
	return collideTest;
}

void Chara::update(double deltaTime)
{
	animation(deltaTime);
}

void Chara::playSound(const char* filePath, float volume, float pitch)
{
	sounds3d[soundIterator]->setPosition(glm::vec3(this->getPositionX(), this->getPositionY(), 100.0f));
	sounds3d[soundIterator]->play(AudioManager::getBufferSound(filePath), volume, pitch);
	soundIterator = (soundIterator + 1) % (int)sounds3d.size();
}

void Chara::initColliderBox()
{
	colliderbox = new Colliderbox(getPositionX() + 10.0f, getPositionY(), 12, 12);
	colliderbox->setColor(255, 0, 0, 128);
}

void Chara::initSounds3d()
{
	for (size_t i = 0; i < sounds3d.size(); i++) {
		sounds3d[i] = new Sound3d();
	}
}

