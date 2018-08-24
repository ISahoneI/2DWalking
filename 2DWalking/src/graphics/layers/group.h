#pragma once

#include "../paints/sprite.h"
#include "../rendering/renderer2d.h"

class Group : public Sprite
{
private:
	std::vector<Sprite*> renderables;
	glm::mat4 transformation;
	
public:
	Group(const glm::mat4& transform);
	~Group();
	void add(Sprite* renderable);
	void submit(Renderer* renderer) const override;
};