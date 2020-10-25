#include "glyph.h"

Glyph::Glyph(char glyph, Texture* texture) : Sprite(texture)
{
	this->glyph = glyph;
	this->texture = texture;
	setIsRender(true);
	setIsVisible(true);
	setLevel(SpriteLevel::FOREGROUND);
}

Glyph::~Glyph()
{
}

void Glyph::setTexUVFont(const char c)
{
	const int indexPos = c - 32;
	const int x = indexPos % (int)getWidth();
	const int y = indexPos / (int)(texture->getHeight() / getHeight());
	setTexUVFont(x, y);
}

void Glyph::setTexUVFont(const int x, const int y)
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

