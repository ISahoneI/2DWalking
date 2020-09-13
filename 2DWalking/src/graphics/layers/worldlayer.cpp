#include "worldlayer.h"

WorldLayer::WorldLayer(Shader* shader) : Layer(new Renderer2D(), shader, glm::ortho(0.0f, 427.0f, 0.0f, 240.0f, -1.0f, 1.0f))
{
}

WorldLayer::~WorldLayer()
{
}

void WorldLayer::add(Sprite* renderable)
{
	Layer::add(renderable);
}

void WorldLayer::add(Chara* chara)
{
	this->renderables.push_back(chara);
	this->renderables.push_back(chara->getColliderbox());
}

void WorldLayer::render()
{
	std::sort(renderables.begin(), renderables.end(), sortByLevelAndYPosition());

	Layer::render();
}
