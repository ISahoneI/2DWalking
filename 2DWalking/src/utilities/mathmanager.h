#pragma once
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class MathManager {
public:

	static void print_elements(const glm::mat4 mat)
	{
		const float *pSource = (const float*)glm::value_ptr(mat);
		for (int i = 0; i < 16; i++)
			std::cout << pSource[i] << ", ";
		std::cout << std::endl;
	}

	static void get_elements(const glm::mat4 mat, float buff[16])
	{
		const float *pSource = (const float*)glm::value_ptr(mat);
		for (int i = 0; i < 16; ++i)
			buff[i] = pSource[i];
	}

	static glm::vec3 multiply_mat4_vec3(const glm::mat4 mat, const glm::vec3 vec)
	{
		const float *pSource = (const float*)glm::value_ptr(mat);
		return glm::vec3(
			pSource[0] * vec.x + pSource[1] * vec.y + pSource[2] * vec.z + pSource[3],
			pSource[4] * vec.x + pSource[5] * vec.y + pSource[6] * vec.z + pSource[7],
			pSource[8] * vec.x + pSource[9] * vec.y + pSource[10] * vec.z + pSource[11]
		);
	}

};