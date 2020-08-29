#pragma once

#include "../rendering/renderer.h"
#include "../paints/texture.h"
#include "../paints/colormanager.h"
#include "../../utilities/mathmanager.h"

class Sprite
{
protected:
	glm::vec3 position;
	glm::vec2 size;
	glm::vec4 colorParameters;
	unsigned int color;
	std::vector<glm::vec2> uv;
	Texture* texture;

public:
	Sprite();
	//Sprite(glm::vec3 position, glm::vec2 size, unsigned int color);
	Sprite(glm::vec3 position, glm::vec2 size, const glm::vec4 color);
	//Sprite(float x, float y, float width, float height, unsigned int color = 0xffffffff);
	Sprite(float x, float y, float width, float height, const glm::vec4 color = glm::vec4(255, 255, 255, 255));
	//Sprite(float x, float y, float width, float height, Texture* texture, unsigned int color = 0xffffffff);
	Sprite(float x, float y, float width, float height, Texture* texture, const glm::vec4 color = glm::vec4(255, 255, 255, 255));

	virtual ~Sprite();

	virtual void submit(Renderer* renderer) const;


	void setPosition(float x, float y, float z = 0.0f) { this->position = glm::vec3(x, y, z); }
	void setPositionX(float x) { this->position.x = x; }
	void setPositionY(float y) { this->position.y = y; }
	void setPositionZ(float z) { this->position.z = z; }

	void setSize(float width, float height) { this->size = glm::vec2(width, height); }
	void setWidth(float width) { this->size.x = width; }
	void setHeight(float height) { this->size.y = height; }

	void setColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
	void setColor(const glm::vec4 color);
	void setColorRed(unsigned int r);
	void setColorGreen(unsigned int g);
	void setColorBlue(unsigned int b);
	void setTransparency(float alpha);


	void setTexture(Texture* tex) { this->texture = tex; }


	const glm::vec3& getPosition() const { return position; }
	const float getPositionX() const { return position.x; }
	const float getPositionY() const { return position.y; }
	const float getPositionZ() const { return position.z; }

	const glm::vec2& getSize() const { return size; }
	const float getWidth() const { return size.x; }
	const float getHeight() const { return size.y; }
	const unsigned int getColor() const { return color; }
	const glm::vec4 getColorParameters() const { return colorParameters; }
	const std::vector<glm::vec2>& getUV() const { return this->uv; }
	const GLuint getTID() const { return this->texture == nullptr ? false : this->texture->getID(); }

private:
	void setTexUV();
};