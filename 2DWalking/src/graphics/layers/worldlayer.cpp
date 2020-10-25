#include "worldlayer.h"

WorldLayer::WorldLayer(Shader* shader) : Layer(new Renderer2D(), shader, glm::ortho(0.0f, 427.0f, 0.0f, 240.0f, -1.0f, 1.0f))
{
	camera = NULL;
	tilemap = NULL;
}

WorldLayer::~WorldLayer()
{
}

void WorldLayer::add(Sprite* renderable)
{
	SpriteLevel lvl = renderable->getLevel();
	if (lvl == SpriteLevel::BACKGROUND)
		backgrounds.push_back(renderable);
	else if ((int)lvl >= 0 && (int)lvl < 5) {
		objects[(int)lvl].push_back(renderable);
	}
	else if (lvl == SpriteLevel::FOREGROUND)
		foregrounds.push_back(renderable);

}

void WorldLayer::add(Chara* chara)
{
	this->add((Sprite*)chara);
	this->add((Sprite*)chara->getColliderbox());
}


void WorldLayer::render()
{
	Layer::render();
}


void WorldLayer::update()
{
	const float xmin = camera->getBordXmin();
	const float xmax = camera->getBordXmax();
	const float ymin = camera->getBordYmin();
	const float ymax = camera->getBordYmax();

	renderables.clear();

	renderables.insert(renderables.begin(), foregrounds.begin(), foregrounds.end());

	for (int lvl = 4; lvl >= 0; lvl--) {
		//Objects to render
		std::sort(objects[lvl].begin(), objects[lvl].end(), sortByYPosition());
		renderables.insert(renderables.begin(), objects[lvl].begin(), objects[lvl].end());

		//TileMap to render (clipping)
		if (tilemap != NULL) {
			levels[lvl].clear();
			for (float x = xmin; x < xmax + 16.0f; x += 16.0f) {
				for (float y = ymin; y < ymax + 16.0f; y += 16.0f) {
					Tile* tile = tilemap->getTileAt(lvl, x, y);
					if (tile != NULL) {
						if (tile->getIsRender() && tile->getIsVisible())
							levels[lvl].push_back(tile);
					}
				}
			}
			renderables.insert(renderables.begin(), levels[lvl].begin(), levels[lvl].end());
		}
	}

	renderables.insert(renderables.begin(), backgrounds.begin(), backgrounds.end());
}
