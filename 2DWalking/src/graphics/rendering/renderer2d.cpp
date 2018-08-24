#include "renderer2d.h"

Renderer2D::Renderer2D()
{
	init();
}

Renderer2D::~Renderer2D()
{
	delete this->ibo;
	glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);
}

void Renderer2D::init()
{
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_UV_INDEX);
	glEnableVertexAttribArray(SHADER_TID_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);

	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
	//glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
	glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
	int offset = 0;
	for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indices[i] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	this->ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
	glBindVertexArray(0);
	//Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer2D::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	this->buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void Renderer2D::submit(const Sprite* sprite)
{
	const glm::vec3& position = sprite->getPosition();
	const glm::vec2& size = sprite->getSize();
	unsigned int color = sprite->getColor();
	const std::vector<glm::vec2>& uv = sprite->getUV();
	const GLuint tid = sprite->getTID();

	//unsigned int coul = 0;
	float ts = 0.0f;
	if (tid > 0)
	{
		bool found = false;
		for (size_t i = 0; i < this->textureSlots.size(); i++)
		{
			if (this->textureSlots[i] == tid)
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}
		if (!found)
		{
			if (this->textureSlots.size() >= RENDERER_MAX_TEXTURES)
			{
				end();
				flush();
				begin();
			}
			this->textureSlots.push_back(tid);
			ts = (float)(this->textureSlots.size());
		}
	}
	/*else
	{
		int r = (int)(color.x * 255.0f);
		int g = (int)(color.y * 255.0f);
		int b = (int)(color.z * 255.0f);
		int a = (int)(color.w * 255.0f);
		coul = a << 24 | b << 16 | g << 8 | r;
	}*/

	//this->buffer->vertex = position;
	//this->buffer->vertex = *this->transformationBack * glm::vec4(position, 1.0f);
	this->buffer->vertex = MathManager::multiply_mat4_vec3(*this->transformationBack, position);
	this->buffer->uv = uv[0];
	this->buffer->tid = ts;
	this->buffer->color = color;
	this->buffer++;

	//this->buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
	//this->buffer->vertex = *this->transformationBack * glm::vec4(position.x, position.y + size.y, position.z, 1.0f);
	this->buffer->vertex = MathManager::multiply_mat4_vec3(*this->transformationBack, glm::vec3(position.x, position.y + size.y, position.z));
	this->buffer->uv = uv[1];
	this->buffer->tid = ts;
	this->buffer->color = color;
	this->buffer++;

	//this->buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
	//this->buffer->vertex = *this->transformationBack * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
	this->buffer->vertex = MathManager::multiply_mat4_vec3(*this->transformationBack, glm::vec3(position.x + size.x, position.y + size.y, position.z));
	this->buffer->uv = uv[2];
	this->buffer->tid = ts;
	this->buffer->color = color;
	this->buffer++;

	//this->buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
	//this->buffer->vertex = *this->transformationBack * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
	this->buffer->vertex = MathManager::multiply_mat4_vec3(*this->transformationBack, glm::vec3(position.x + size.x, position.y, position.z));
	this->buffer->uv = uv[3];
	this->buffer->tid = ts;
	this->buffer->color = color;
	this->buffer++;

	this->indexCount += 6;
}

void Renderer2D::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer2D::flush()
{
	for (size_t i = 0; i < this->textureSlots.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->textureSlots[i]);
	}
	glBindVertexArray(this->vao);
	this->ibo->bind();

	glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, NULL);

	this->ibo->unbind();
	glBindVertexArray(0);

	this->indexCount = 0;
	this->textureSlots.clear();
}
