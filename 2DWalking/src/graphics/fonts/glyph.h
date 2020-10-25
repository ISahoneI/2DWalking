#pragma once

#include "../paints/sprite.h"

class Glyph : public Sprite
{
private:
	char glyph;


public:
	Glyph(char glyph, Texture* texture);
	~Glyph();

	void setTexUVFont(const char c);
	void setTexUVFont(const int x, const int y);

};