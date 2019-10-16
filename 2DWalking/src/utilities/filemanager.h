#pragma once

#include <iostream>
#include <string>
#include <stb_image/stb_image.h>

class FileManager
{
public:
	static std::string read_file(const char* path)
	{
		FILE* file = fopen(path, "rt");
		if (file == nullptr)
		{
			std::cout << "Could not find the file : " << path << " !" << std::endl;
			return std::string();
		}
		fseek(file, 0, SEEK_END);
		unsigned long lenght = ftell(file);
		char* data = new char[lenght + 1];
		memset(data, 0, lenght + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, lenght, file);
		fclose(file);

		std::string res(data);
		delete[] data;
		return res;
	}

	static unsigned char* load_image(const char* path, int* ptr_width, int* ptr_height, int* ptr_nbColor)
	{
		unsigned char* data = stbi_load(path, ptr_width, ptr_height, ptr_nbColor, STBI_rgb_alpha);

		if (data)
			return data;
		std::cout << "Failed to load the texture " << path << " !" << std::endl;
		stbi_image_free(data);
		return NULL;
	}

	static void free_image(unsigned char* data)
	{
		stbi_image_free(data);
	}
};
