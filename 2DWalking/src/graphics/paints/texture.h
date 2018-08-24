#pragma once

#include <string>
#include <GL/glew.h>
#include "../../utilities/filemanager.h"

class Texture
{
private:
	std::string fileName;
	GLuint id;
	GLsizei width, height;
	int nbColor;

public:
	Texture(const std::string& fileName);
	~Texture();
	void bind() const;
	void unbind() const;

	 const unsigned int getID() const { return this->id; }
	 const unsigned int getWidth() const { return this->width; }
	 const unsigned int getHeight() const { return this->height; }
	 const unsigned int getnbColor() const { return this->nbColor; }

private:
	GLuint load();
};