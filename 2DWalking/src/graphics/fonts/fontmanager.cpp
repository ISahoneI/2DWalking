#include "fontmanager.h"

std::map <std::string, FontInfo*> FontManager::fontInfos;
std::map <std::string, Texture*> FontManager::fontTextures;

FontManager::FontManager()
{
	fontInfos = {
		{ "arial20", FontManager::loadFontInfo(DW_FONTINFO_1) },
		{ "arial16", FontManager::loadFontInfo(DW_FONTINFO_2) },
		{ "msgothic12", FontManager::loadFontInfo(DW_FONTINFO_3) }
	};

	fontTextures = {
		{ "arial20", new Texture(DW_FONT_1) },
		{ "arial16", new Texture(DW_FONT_2) },
		{ "msgothic12", new Texture(DW_FONT_3) }
	};
}

FontManager::~FontManager()
{
	for (auto it = fontInfos.begin(); it != fontInfos.end(); ++it)
		delete it->second;
	for (auto it = fontTextures.begin(); it != fontTextures.end(); ++it)
		delete it->second;
}

Text* FontManager::getTextToRender(const std::string& content, const std::string& fontName)
{
	Text* text = new Text(content, fontInfos.at(fontName), fontTextures.at(fontName));
	return text;
}



FontInfo* FontManager::loadFontInfo(const char* filePath)
{
	FontInfo* fontInfo = new FontInfo();
	std::ifstream file(filePath);
	std::string line;
	int itCharWidth = 0;
	while (std::getline(file, line))
	{
		std::string data = line.substr(line.find(",") + 1);
		if (line.find("Image Width") != std::string::npos) {
			fontInfo->imageSize[0] = std::stoi(data);
		}
		if (line.find("Image Height") != std::string::npos) {
			fontInfo->imageSize[1] = std::stoi(data);
		}
		if (line.find("Cell Width") != std::string::npos) {
			fontInfo->cellSize[0] = std::stoi(data);
		}
		if (line.find("Cell Height") != std::string::npos) {
			fontInfo->cellSize[1] = std::stoi(data);
		}
		if (line.find("Base Width") != std::string::npos) {
			fontInfo->charWidths[itCharWidth] = std::stoi(data);
			itCharWidth++;
		}
	}
	return fontInfo;
}

