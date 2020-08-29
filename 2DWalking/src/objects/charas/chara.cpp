#include "chara.h"

Chara::Chara() : Sprite(360, 120, 32, 40, new Texture("res/textures/spritesheet/Heros_Yzao.png"), glm::vec4(255, 254, 253, 252))
{
	//Sprite(12, 8, 0.6f * 24 / 16, 0.6f * 32 / 16, new Texture("res/textures/spritesheet/Heros_Yzao.png"), ColorManager::getHexaColori(255, 254, 253, 252))
	setTexUVSpriteSheet(1, 2);
	colliderbox = new Colliderbox();
	colliderbox->setSize(16, 12);
	colliderbox->setColor(255, 0, 0, 128);
	colliderbox->setPosition(getPositionX() + 8.0f, getPositionY());

	/*Xcolliderbox = new Colliderbox();
	Xcolliderbox->setSize(17, 11);
	Xcolliderbox->setColor(0.0f, 0.0f, 1.0f, 0.5f);
	Xcolliderbox->setPosition(getPositionX() + 7.0f, getPositionY() + 1.0f);

	Ycolliderbox = new Colliderbox();
	Ycolliderbox->setSize(15, 13);
	Ycolliderbox->setColor(1.0f, 0.0f, 0.0f, 0.5f);
	Ycolliderbox->setPosition(getPositionX() + 8.0f, getPositionY());*/
	//setTransparency(0.0f);
}

Chara::~Chara()
{
}

void Chara::move(float x, float y, CharaDirection direction)
{
	float distX = getPositionX() - x;
	float distY = getPositionY() - y;

	if (distX != 0.0f || distY != 0.0f) {
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
			//colliderbox->setPosition(getPositionX() + colliderbox->getWidth() / 2.0f - distX, getPositionY() + 1);
			colliderbox->setPositionX(x + 8.0f);
		}
		if (distY != 0.0f) {
			setPositionY(y);
			//colliderbox->setPosition(getPositionX() + colliderbox->getWidth() / 2.0f, getPositionY() + 1 - distY);
			colliderbox->setPositionY(y);
		}
		//Xcolliderbox->setPosition(getPositionX() + 7.0f, getPositionY() + 1.0f);
		//Ycolliderbox->setPosition(getPositionX() + 8.0f, getPositionY());
	}
}

void Chara::setDirection(CharaDirection direction)
{
	if (direction == CharaDirection::DOWN)
		setTexUVSpriteSheet(1, 2);
	else if (direction == CharaDirection::UP)
		setTexUVSpriteSheet(1, 0);
	else if (direction == CharaDirection::LEFT)
		setTexUVSpriteSheet(1, 3);
	else if (direction == CharaDirection::RIGHT)
		setTexUVSpriteSheet(1, 1);
}

void Chara::setTexUVSpriteSheet(const int x, const int y)
{
	uv.clear();
	const float tx = (float)(x * 32.0f) / 640.0f;
	const float ty = (float)(y * 40.0f) / 640.0f;
	const float w = (float)32.0f / 640.0f;
	const float h = (float)40.0f / 640.0f;
	uv.push_back(glm::vec2(tx, h + ty));
	uv.push_back(glm::vec2(tx, ty));
	uv.push_back(glm::vec2(w + tx, ty));
	uv.push_back(glm::vec2(w + tx, h + ty));
}

