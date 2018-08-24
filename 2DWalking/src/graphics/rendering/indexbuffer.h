#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private:
	GLuint id;
	GLuint count;

public:
	IndexBuffer(GLushort* data, GLsizei count);
	IndexBuffer(GLuint* data, GLsizei count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	 GLuint getCount() { return count; }
};