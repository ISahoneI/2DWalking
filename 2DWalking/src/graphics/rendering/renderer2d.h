#pragma once

#include "renderer.h"
#include "indexbuffer.h"
#include "../paints/sprite.h"

#define RENDERER_MAX_SPRITES	100000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	64

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

struct VertexData
{
	glm::vec3 vertex;
	glm::vec2 uv;
	float tid;
	unsigned int color;
};

class Renderer2D : public Renderer
{
private:
	GLuint vao;
	GLuint vbo;
	VertexData* buffer;
	IndexBuffer* ibo;
	GLsizei indexCount;

	std::vector<GLuint> textureSlots;
	
public:
	Renderer2D();
	~Renderer2D();

	void begin() override;
	void submit(const Sprite* renderable) override;
	void end() override;
	void flush() override;

private:
	void init();
};