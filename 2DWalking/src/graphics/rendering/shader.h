#pragma once

#include <GL/glew.h>
#include <iostream>
#include <vector>
#include "../../utilities/filemanager.h"
#include "../../utilities/mathmanager.h"

class Shader {
private:
	GLuint id;
	const char* vertPath;
	const char* fragPath;

public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();


	void enable() const;
	void disable() const;

	GLint getUniformLocation(const GLchar* name);
	void setUniform1f(const GLchar* name, float value);
	void setUniform1fv(const GLchar* name, float* value, int count);
	void setUniform1i(const GLchar* name, int value);
	void setUniform1iv(const GLchar* name, int* value, int count);
	void setUniform2f(const GLchar* name, const glm::vec2& vector);
	void setUniform3f(const GLchar* name, const glm::vec3& vector);
	void setUniform4f(const GLchar* name, const glm::vec4& vector);
	void setUniformMat4(const GLchar* name, const glm::mat4& matrix);



	 GLuint getID() const { return id; }

private:
	GLuint init();
};