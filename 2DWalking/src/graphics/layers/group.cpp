#include "group.h"

Group::Group(const glm::mat4& transform)
{
	this->transformation = transform;
}

Group::~Group()
{
	for (size_t i = 0; i < renderables.size(); i++)
		delete this->renderables[i];
}

void Group::add(Sprite* renderable)
{
	this->renderables.push_back(renderable);
}

void Group::submit(Renderer* renderer) const
{
	renderer->push(this->transformation);
	for (const Sprite* renderable : this->renderables)
		renderable->submit(renderer);
	renderer->pop();
}