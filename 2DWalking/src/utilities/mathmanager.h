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
		const float *pSound = (const float*)glm::value_ptr(mat);
		for (int i = 0; i < 16; i++)
			std::cout << pSound[i] << ", ";
		std::cout << std::endl;
	}

	static void get_elements(const glm::mat4 mat, float buff[16])
	{
		const float *pSound = (const float*)glm::value_ptr(mat);
		for (int i = 0; i < 16; ++i)
			buff[i] = pSound[i];
	}

	static glm::vec3 multiply_mat4_vec3(const glm::mat4 mat, const glm::vec3 vec)
	{
		const float *pSound = (const float*)glm::value_ptr(mat);
		return glm::vec3(
			pSound[0] * vec.x + pSound[1] * vec.y + pSound[2] * vec.z + pSound[3],
			pSound[4] * vec.x + pSound[5] * vec.y + pSound[6] * vec.z + pSound[7],
			pSound[8] * vec.x + pSound[9] * vec.y + pSound[10] * vec.z + pSound[11]
		);
	}

};