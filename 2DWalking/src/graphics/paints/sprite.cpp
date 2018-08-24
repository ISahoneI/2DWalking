#include "sprite.h"

Sprite::Sprite()
{
	setTexUV();
}

Sprite::Sprite(glm::vec3 position, glm::vec2 size, unsigned int color)
{
	this->position = position;
	this->size = size;
	this->color = color;

	setTexUV();
}

Sprite::Sprite(glm::vec3 position, glm::vec2 size, const glm::vec4& color)
{
	this->position = position;
	this->size = size;
	setColor(color);

	setTexUV();
}

Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
	: Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), color)
{
}

Sprite::Sprite(float x, float y, float width, float height, const glm::vec4 & color)
	: Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), color)
{
}

Sprite::Sprite(float x, float y, float width, float height, Texture * texture, unsigned int color)
	: Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), color)
{
	this->texture = texture;
}

Sprite::~Sprite(){}

void Sprite::submit(Renderer * renderer) const
{
	renderer->submit(this);
}

void Sprite::setTransparency(float alpha)
{

}

void Sprite::setTexUV()
{
	uv.push_back(glm::vec2(0, 1));
	uv.push_back(glm::vec2(0, 0));
	uv.push_back(glm::vec2(1, 0));
	uv.push_back(glm::vec2(1, 1));
}
