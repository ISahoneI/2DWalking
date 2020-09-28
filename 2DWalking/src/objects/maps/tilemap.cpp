#include "tilemap.h"

TileMap::TileMap(Texture* tileset, const char* xmlMapPath)
{
	xmlFileName = xmlMapPath;
	this->tileset = tileset;

	loadMapFromXml(xmlMapPath);
}

TileMap::~TileMap()
{
}

void TileMap::loadMapFromXml(const char* xmlMapPath)
{
	xmlMapFile = new rapidxml::file<>(xmlMapPath);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlMapFile->data());
	rapidxml::xml_node<>* node = doc.first_node();

	width = atoi(node->first_attribute("width")->value());
	height = atoi(node->first_attribute("height")->value());
	tilewidth = atoi(node->first_attribute("tilewidth")->value());
	tileheight = atoi(node->first_attribute("tileheight")->value());
	std::vector<std::string> dataTile;

	int lvl = 0;
	for (rapidxml::xml_node<>* child = node->first_node(); child; child = child->next_sibling())
	{
		rapidxml::xml_node<>* nodeData = child->first_node();

		if (nodeData != nullptr) {
			float posX = 0;	float posY = (float)((height * tileheight));

			std::stringstream s_stream(nodeData->value());
			while (s_stream.good()) {
				std::string substr;
				getline(s_stream, substr, ',');
				substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());
				substr.erase(std::remove(substr.begin(), substr.end(), '\n'), substr.end());
				dataTile.push_back(substr);
			}
			for (size_t i = 0; i < dataTile.size(); i++) {
				if (i % width == 0) {
					posY -= tileheight;
					posX = 0.0f;
				}

				int idTile = stoi(dataTile.at(i));
				if (idTile > 0) {
					Tile* tile = new Tile(posX, posY, (float)tilewidth, (float)tileheight, tileset, (SpriteLevel)lvl);
					tile->setTexUVTileset(idTile);
					levels[lvl].push_back(tile);
				}

				posX += tilewidth;
			}
			if (strcmp(child->name(), "layer") == 0) {
				lvl++;
				dataTile.clear();
			}
		}
	}
}

