#include "layer.h"

Layer::Layer(Renderer2D* renderer, Shader* shader, glm::mat4 projection)
{
	this->renderer = renderer;
	this->shader = shader;
	this->projection = projection;

	this->shader->enable();
	this->shader->setUniformMat4("projection_mat", projection);
	GLint texIDs[] =
	{
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
		20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
		30, 31
	};
	this->shader->setUniform1iv("textures", texIDs, 32);
	this->shader->disable();
}

Layer::Layer(Shader* shader)
	: Layer(new Renderer2D(), shader, glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f))
{

}

Layer::~Layer()
{
	delete this->shader;
	delete this->renderer;
	for (size_t i = 0; i < this->renderables.size(); i++)
		delete this->renderables[i];
}

void Layer::add(Sprite* renderable)
{
	this->renderables.push_back(renderable);
}

void Layer::render()
{
	this->shader->enable();

	this->renderer->begin();
	for (const Sprite* renderable : this->renderables)
		renderable->submit(this->renderer);
	//this->renderer->submit(renderable);

	this->renderer->end();
	this->renderer->flush();
}
