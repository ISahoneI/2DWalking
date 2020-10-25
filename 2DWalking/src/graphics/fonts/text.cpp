#include "text.h"



Text::Text(const std::string& text, FontInfo* fontInfo, Texture* font) : Group()
{
	this->text = text;
	this->fontInfo = fontInfo;
	this->font = font;
	setIsVisible(true);
	setIsRender(true);
	setLevel(SpriteLevel::FOREGROUND);
	setPosition(0.0f, ENGINE_RESOLUTION_Y / 2.0f);
	createTextSprites();
}

Text::~Text()
{

}



void Text::add(Glyph* renderable)
{
	Group::add(renderable);
}

void Text::createTextSprites()
{
	int posX = (int)getPositionX();
	int posY = (int)getPositionY();
	for (char& c : this->text) {
		Glyph* glyph = new Glyph(c, font);
		glyph->setPosition((float)posX, (float)posY);
		glyph->setSize((float)fontInfo->cellSize[0], (float)fontInfo->cellSize[1]);
		glyph->setTexUVFont(c);

		add(glyph);
		if (c != '\n')
			posX += fontInfo->charWidths[c - 32];
		else {
			posX = (int)getPositionX();
			posY -= fontInfo->cellSize[1];
		}

	}
}

