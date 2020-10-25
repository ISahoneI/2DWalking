#pragma once

#include "../layers/group.h"
#include "glyph.h"
#include "../../utilities/global.h"

struct FontInfo {
	int imageSize[2];
	int cellSize[2];
	int charWidths[224];
};

class Text : public Group {

private:
	std::string text;

	FontInfo* fontInfo;
	Texture* font;

public:
	Text(const std::string& text, FontInfo* fontInfo, Texture* font);
	~Text();


	void add(Glyph* renderable);

private:
	void createTextSprites();

};