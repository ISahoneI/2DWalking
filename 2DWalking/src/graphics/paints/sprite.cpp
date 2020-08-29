#include "sprite.h"

Sprite::Sprite()
{
	this->texture = NULL;
	setTexUV();
}

Sprite::Sprite(glm::vec3 position, glm::vec2 size, const glm::vec4 color)
{
	this->position = position;
	this->size = size;
	setColor(color);
	this->texture = NULL;
	setTexUV();
}

Sprite::Sprite(float x, float y, float width, float height, const glm::vec4 color)
	: Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), color)
{
}
Sprite::Sprite(float x, float y, float width, float height, Texture* texture, const glm::vec4 color)
	: Sprite(glm::vec3(x, y, 0), glm::vec2(width, height), color)
{
	this->texture = texture;
}

Sprite::~Sprite() {}

void Sprite::submit(Renderer* renderer) const
{
	renderer->submit(this);
}

void Sprite::setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	this->colorParameters = glm::vec4(r, g, b, a);
	this->color = ColorManager::getHexaColori(r, g, b, a);
}

void Sprite::setColor(const glm::vec4 color)
{
	this->colorParameters = color;
	this->color = ColorManager::getHexaColori((unsigned int)color.x, (unsigned int)color.y, (unsigned int)color.z, (unsigned int)color.w);
}

void Sprite::setColorRed(unsigned int r)
{
	this->colorParameters = glm::vec4(r, (unsigned int)colorParameters.y, (unsigned int)colorParameters.z, (unsigned int)colorParameters.w);
	this->color = ColorManager::getHexaColori(r, (unsigned int)colorParameters.y, (unsigned int)colorParameters.z, (unsigned int)colorParameters.w);
}

void Sprite::setColorGreen(unsigned int g)
{
	this->colorParameters = glm::vec4((unsigned int)colorParameters.x, g, (unsigned int)colorParameters.z, (unsigned int)colorParameters.w);
	this->color = ColorManager::getHexaColori((unsigned int)colorParameters.x, g, (unsigned int)colorParameters.z, (unsigned int)colorParameters.w);
}

void Sprite::setColorBlue(unsigned int b)
{

	this->colorParameters = glm::vec4((unsigned int)colorParameters.x, (unsigned int)colorParameters.y, b, (unsigned int)colorParameters.w);
	this->color = ColorManager::getHexaColori((unsigned int)colorParameters.x, (unsigned int)colorParameters.y, b, (unsigned int)colorParameters.w);
}



void Sprite::setTransparency(float alpha)
{
	unsigned int aCoul = (unsigned int)(alpha * 255.0f);
	this->colorParameters = glm::vec4((unsigned int)colorParameters.x, (unsigned int)colorParameters.y, (unsigned int)colorParameters.z, aCoul);
	this->color = ColorManager::getHexaColori((unsigned int)colorParameters.x, (unsigned int)colorParameters.y, (unsigned int)colorParameters.z, aCoul);
}



void Sprite::setTexUV()
{
	uv.push_back(glm::vec2(0, 1));
	uv.push_back(glm::vec2(0, 0));
	uv.push_back(glm::vec2(1, 0));
	uv.push_back(glm::vec2(1, 1));
}
