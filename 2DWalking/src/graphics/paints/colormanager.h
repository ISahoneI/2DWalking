#pragma once

class ColorManager {
public:
	static unsigned int getHexaColori(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
	{
		return a << 24 | b << 16 | g << 8 | r;
	}

	static unsigned int getHexaColorf(float r, float g, float b, float a)
	{
		unsigned int rCoul = (unsigned int)(r * 255.0f);
		unsigned int gCoul = (unsigned int)(g * 255.0f);
		unsigned int bCoul = (unsigned int)(b * 255.0f);
		unsigned int aCoul = (unsigned int)(a * 255.0f);
		return ColorManager::getHexaColori(rCoul, gCoul, bCoul, aCoul);
	}

	static unsigned int getHexaColorRed(const unsigned int& color)
	{
		//!\ NOT OPTIMAL !!!
		return color / (255 * 255 * 255);
	}

	static unsigned int getHexaColorGreen(const unsigned int& color)
	{
		//!\ NOT OPTIMAL !!!
		return (color >> 8) / (255 * 255);
	}

	static unsigned int getHexaColorBlue(const unsigned int& color)
	{
		//!\ NOT OPTIMAL !!!
		return (color >> 16) / 255;
	}

	static unsigned int getHexaColorAlpha(const unsigned int& color)
	{
		return color >> 24;
	}

	static unsigned int setHexaColorAlphai(unsigned int& color, unsigned int alpha)
	{
		;
	}
};