#pragma once

#include "tile.h"
#include "../../utilities/externlibs/rapidxml_utils.hpp"

#include <sstream>
#include <algorithm>

class TileMap {

private:

	std::string xmlFileName;
	rapidxml::file<>* xmlMapFile;

	std::vector<Tile*> levels[5];

	int width, height;
	int tilewidth, tileheight;

	Texture* tileset;


public:

	TileMap(Texture* tileset, const char* xmlMapPath);
	~TileMap();

	std::vector<Tile*> getLevels(int lvl) { return levels[lvl]; }
	Tile* getTileAt(const int lvl, const float x, const float y);

private:

	void loadMapFromXml(const char* xmlMapPath);

};