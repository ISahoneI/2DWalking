#include "worldlayer.h"

WorldLayer::WorldLayer(Shader* shader) : Layer(new Renderer2D(), shader, glm::ortho(0.0f, 427.0f, 0.0f, 240.0f, -1.0f, 1.0f))
{
}

WorldLayer::~WorldLayer()
{
}

void WorldLayer::add(Sprite* renderable)
{
	SpriteLevel lvl = renderable->getLevel();
	if (lvl == SpriteLevel::BACKGROUND)
		backgrounds.push_back(renderable);
	else if ((int)lvl >= 0 && (int)lvl < 5)
		levels[(int)lvl].push_back(renderable);
	else if (lvl == SpriteLevel::FOREGROUND)
		foregrounds.push_back(renderable);

	update();
}

void WorldLayer::add(Chara* chara)
{
	this->add((Sprite*)chara);
	this->add((Sprite*)chara->getColliderbox());
}

void WorldLayer::add(TileMap* tilemap)
{
	for (int i = 0; i < 5; i++) {
		for (Tile* tile : tilemap->getLevels(i)) {
			levels[i].push_back((Sprite*)tile);
		}
	}
	update();
}

void WorldLayer::render()
{
	//update();

	Layer::render();
}


void WorldLayer::update()
{
	renderables.clear();

	renderables.insert(renderables.begin(), foregrounds.begin(), foregrounds.end());
	for (int lvl = 4; lvl >= 0; lvl--) {
		std::sort(levels[lvl].begin(), levels[lvl].end(), sortByYPosition());
		renderables.insert(renderables.begin(), levels[lvl].begin(), levels[lvl].end());
	}
	renderables.insert(renderables.begin(), backgrounds.begin(), backgrounds.end());
}

void WorldLayer::update(Camera camera)
{
	const float xmin = camera.getPosRefX() - (ENGINE_RESOLUTION_X * 0.5f) * camera.getZoom();
	const float xmax = camera.getPosRefX() + (ENGINE_RESOLUTION_X * 0.5f) * camera.getZoom();
	const float ymin = camera.getPosRefY() - (ENGINE_RESOLUTION_Y * 0.5f) * camera.getZoom();
	const float ymax = camera.getPosRefY() + (ENGINE_RESOLUTION_Y * 0.5f) * camera.getZoom();

	renderables.clear();

	renderables.insert(renderables.begin(), foregrounds.begin(), foregrounds.end());
	for (int lvl = 4; lvl >= 0; lvl--) {
		std::sort(levels[lvl].begin(), levels[lvl].end(), sortByYPosition());
		renderables.insert(renderables.begin(), levels[lvl].begin(), levels[lvl].end());
		auto it = std::remove_if(renderables.begin(),
			renderables.end(),
			[xmin, xmax, ymin, ymax](Sprite* renderable) {
				return !(renderable->getPositionX() + renderable->getWidth() > xmin&& renderable->getPositionX() < xmax
					&& renderable->getPositionY() + renderable->getHeight() > ymin&& renderable->getPositionY() < ymax);
			});

		renderables.erase(it, renderables.end());
	}
	renderables.insert(renderables.begin(), backgrounds.begin(), backgrounds.end());
}

void WorldLayer::clipping(Camera camera)
{
	const float xmin = camera.getPosRefX() - (ENGINE_RESOLUTION_X * 0.5f) * camera.getZoom();
	const float xmax = camera.getPosRefX() + (ENGINE_RESOLUTION_X * 0.5f) * camera.getZoom();
	const float ymin = camera.getPosRefY() - (ENGINE_RESOLUTION_Y * 0.5f) * camera.getZoom();
	const float ymax = camera.getPosRefY() + (ENGINE_RESOLUTION_Y * 0.5f) * camera.getZoom();
	int i = 0;
	for (Sprite* renderable : this->renderables) {
		if (!(renderable->getPositionX() + renderable->getWidth() > xmin&& renderable->getPositionX() < xmax
			&& renderable->getPositionY() + renderable->getHeight() > ymin&& renderable->getPositionY() < ymax)) {
			renderable->setIsRender(false);
		}
		else
			renderable->setIsRender(true);
		i++;
	}
}

