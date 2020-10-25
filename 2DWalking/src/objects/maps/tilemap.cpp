#include "tilemap.h"

TileMap::TileMap(Texture* tileset, const char* xmlMapPath)
{
	xmlFileName = xmlMapPath;
	this->tileset = tileset;

	loadMapFromXml(xmlMapPath);
}

TileMap::~TileMap()
{
	for (int lvl = 0; lvl < 5; lvl++) {
		for (size_t i = 0; i < colliders.size(); i++)
			delete levels[lvl][i];
	}
	for (size_t i = 0; i < colliders.size(); i++)
		delete colliders[i];
	delete tileset;
}

Tile* TileMap::getTileAt(const int lvl, const float x, const float y)
{
	int index = (int)(x / tilewidth) + (height * width) - height - (int)(y / tileheight) * width;
	if (lvl < 0 || lvl >= 4)
		return NULL;
	if (index < 0 || index >= (int)levels[lvl].size())
		return NULL;
	//std::cout << "x:" << (int)(x / 16) << " y:" << (int)(y / 16) << " index:" << index << std::endl;
	return levels[lvl].at(index);
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
		if (strcmp(child->name(), "layer") == 0) {
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
						tile->setIdTile(idTile);
						tile->setTexUVTileset(idTile);
						levels[lvl].push_back(tile);
					}
					else {
						Tile* tile = new Tile(posX, posY, (float)tilewidth, (float)tileheight, (SpriteLevel)lvl);
						tile->setIdTile(idTile);
						levels[lvl].push_back(tile);
					}

					posX += tilewidth;
				}

				lvl++;
				dataTile.clear();
			}
		}
		else if (strcmp(child->name(), "objectgroup") == 0) {
			if (strcmp(child->first_attribute("name")->value(), "COLLIDERS") == 0) {
				for (rapidxml::xml_node<>* colliderData = child->first_node(); colliderData; colliderData = colliderData->next_sibling()) {
					float collX = (float)atoi(colliderData->first_attribute("x")->value());

					float collW = (float)atoi(colliderData->first_attribute("width")->value());
					float collH = (float)atoi(colliderData->first_attribute("height")->value());
					float collY = (height * 16) - (float)atoi(colliderData->first_attribute("y")->value()) - collH;
					colliders.push_back(new Colliderbox(collX, collY, collW, collH));
				}
			}
		}
		else if (strcmp(child->name(), "imagelayer") == 0) {

		}
	}
}

