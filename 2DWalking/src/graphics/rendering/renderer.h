#pragma once

#include <vector>
#include <GL/glew.h>
#include "../../utilities/mathmanager.h"

class Sprite;

class Renderer
{
protected:
	std::vector <glm::mat4> transformationStack;
	const glm::mat4* transformationBack;
protected:
	Renderer()
	{
		this->transformationStack.push_back(glm::mat4(1.0f));
		this->transformationBack = &this->transformationStack.back();
	}
public:
	void push(const glm::mat4& matrix, bool isOverride = false)
	{
		if (isOverride)
			this->transformationStack.push_back(matrix);
		else
			this->transformationStack.push_back(this->transformationStack.back() * matrix);
		this->transformationBack = &this->transformationStack.back();
	}

	void pop()
	{
		if (this->transformationStack.size() > 1)
			this->transformationStack.pop_back();
		this->transformationBack = &this->transformationStack.back();
	}
		
	virtual void begin() = 0;
	virtual void submit(const Sprite* renderable) = 0;
	virtual void end() = 0;
	virtual void flush() = 0;
};