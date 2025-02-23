#pragma once
#include <fstream>
#include <iostream>
#include <math.h>
#include "Vec3.h"
#include "Constants.h"

class ImageGenerator
{
	const size_t m_width, m_height;

	void setPixels(std::ofstream& outputFile);
public:
	ImageGenerator(size_t width, size_t height) : m_height(height), m_width(width) {};

	bool generateImage();
};