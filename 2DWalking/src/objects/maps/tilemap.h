#pragma once

#include "tile.h"
#include <rapidxml_utils.hpp>

#include <sstream>
#include <algorithm>

class TileMap {

private:

	std::string xmlFileName;
	rapidxml::file<>* xmlMapFile;

	std::vector<Tile*> levels[5];
	std::vector<Colliderbox*> colliders;

	int width, height;
	int tilewidth, tileheight;

	Texture* tileset;


public:

	TileMap(Texture* tileset, const char* xmlMapPath);
	~TileMap();

	std::vector<Tile*> getLevels(int lvl) { return levels[lvl]; }
	Tile* getTileAt(const int lvl, const float x, const float y);

	const std::vector<Colliderbox*> getColliders() const { return colliders; }

private:

	void loadMapFromXml(const char* xmlMapPath);

};