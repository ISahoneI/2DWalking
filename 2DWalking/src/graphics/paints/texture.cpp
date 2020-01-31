#include "texture.h"


Texture::Texture(const std::string& fileName)
{
	this->fileName = fileName;
	this->id = load();
}

Texture::~Texture(){}

GLuint Texture::load()
{
	unsigned char* data = FileManager::load_image(this->fileName.c_str(), &this->width, &this->height, &this->nbColor);
	///TODO (Lancer une exception sinon NullPointer ERROR)
	if (!data)
		return NULL;
	GLuint res;
	glGenTextures(1, &res);
	glBindTexture(GL_TEXTURE_2D, res);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	FileManager::free_image(data);
	return res;
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}