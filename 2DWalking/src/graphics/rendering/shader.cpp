#include "shader.h"

Shader::Shader(const char* vertPath, const char* fragPath)
{
	this->vertPath = vertPath;
	this->fragPath = fragPath;
	this->id = init();
}

Shader::~Shader()
{
	glDeleteProgram(this->id);
}

GLuint Shader::init()
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertStr = FileManager::read_file(this->vertPath);
	std::string fragStr = FileManager::read_file(this->fragPath);
	const char* vertSrc = vertStr.c_str();
	const char* fragSrc = fragStr.c_str();

	GLint test_load;
	//LOADING the Vertex Shader
	glShaderSource(vertex, 1, &vertSrc, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &test_load);
	if (test_load == GL_FALSE)
	{
		GLint size_error;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &size_error);
		std::vector<char> error(size_error);
		glGetShaderInfoLog(vertex, size_error, &size_error, &error[0]);
		std::cout << "VERTEX ERROR : " << &error[0] << std::endl;
		glDeleteShader(vertex);
		return 0;
	}
	//LOADING the Fragment Shader
	glShaderSource(fragment, 1, &fragSrc, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &test_load);
	if (test_load == GL_FALSE)
	{
		GLint size_error;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &size_error);
		std::vector<char> error(size_error);
		glGetShaderInfoLog(fragment, size_error, &size_error, &error[0]);
		std::cout << "FRAGMENT ERROR : " << &error[0] << std::endl;
		glDeleteShader(fragment);
		return 0;
	}

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

void Shader::enable() const
{
	glUseProgram(this->id);
}

void Shader::disable() const
{
	glUseProgram(0);
}

GLint Shader::getUniformLocation(const GLchar* name)
{
	return glGetUniformLocation(this->id, name);
}

void Shader::setUniform1f(const GLchar* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform1fv(const GLchar* name, float* value, int count)
{
	glUniform1fv(getUniformLocation(name), count, value);
}

void Shader::setUniform1i(const GLchar* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform1iv(const GLchar* name, int* value, int count)
{
	glUniform1iv(getUniformLocation(name), count, value);
}

void Shader::setUniform2f(const GLchar* name, const glm::vec2& vector)
{
	glUniform2f(getUniformLocation(name), vector.x, vector.y);
}

void Shader::setUniform3f(const GLchar* name, const glm::vec3& vector)
{
	glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
}

void Shader::setUniform4f(const GLchar* name, const glm::vec4& vector)
{
	glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setUniformMat4(const GLchar* name, const glm::mat4& matrix)
{
	float elms[16];
	MathManager::get_elements(matrix, elms);
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, elms);
}

