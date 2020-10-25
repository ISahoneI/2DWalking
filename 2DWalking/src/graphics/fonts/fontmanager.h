#pragma once

#include <vector>
#include <map>
#include <fstream>
#include "text.h"
#include "fontpaths.h"

class FontManager {

private:
	static std::map <std::string, FontInfo*> fontInfos;
	static std::map <std::string, Texture*> fontTextures;

public:

	FontManager();
	~FontManager();

	static Text* getTextToRender(const std::string& content, const std::string& fontName);

private:
	FontInfo* loadFontInfo(const char* filePath);

};