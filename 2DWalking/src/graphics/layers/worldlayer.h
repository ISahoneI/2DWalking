#pragma once

#include "layer.h"
#include "../../objects/charas/chara.h"
#include "../../objects/maps/tilemap.h"
#include "../../inputs/camera.h"

#include "../../utilities/global.h"

class WorldLayer : public Layer
{
private:
	std::vector<Sprite*> backgrounds;
	std::vector<Sprite*> levels[5];
	std::vector<Sprite*> foregrounds;

	TileMap* tilemap;
	std::vector<Sprite*> objects[5];
	Camera* camera;

public:
	WorldLayer(Shader* shader);
	~WorldLayer();

	void add(Sprite* renderable);
	void add(Chara* chara);
	void render();
	//void update();
	void update();

	Camera* getCamera() { return camera; }
	void setCamera(Camera* camera) { this->camera = camera; }

	TileMap* getTilemap() { return  tilemap; }
	void setTilemap(TileMap* tilemap) { this->tilemap = tilemap; }

	struct sortByYPosition
	{
		inline bool operator() (Sprite* sprite1, Sprite* sprite2)
		{
			return sprite1->getPositionY() > sprite2->getPositionY();
		}
	};

	struct sortByLevelAndYPosition
	{
		inline bool operator() (Sprite* sprite1, Sprite* sprite2)
		{
			if ((int)sprite1->getLevel() != (int)sprite2->getLevel()) {
				return ((int)sprite1->getLevel() < (int)sprite2->getLevel());
			}
			else {
				return sprite1->getPositionY() > sprite2->getPositionY();
			}
		}
	};

};