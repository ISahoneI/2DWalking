#pragma once

#include "../rendering/renderer2d.h"
#include "../rendering/shader.h"
#include "../paints/sprite.h"
#include <array>
#include <algorithm>

class Layer
{
protected:
	Renderer2D* renderer;
	std::vector<Sprite*> renderables;
	Shader* shader;
	glm::mat4 projection;

protected:
	Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projection);
public:
	Layer(Shader* shader);
	virtual ~Layer();
	virtual void add(Sprite* renderable);
	virtual void render();


	const std::vector<Sprite*>& getRenderables() const { return this->renderables; }

};