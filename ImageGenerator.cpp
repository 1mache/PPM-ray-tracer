#include "ImageGenerator.h"
#include <cmath>
void ImageGenerator::setPixels(std::ofstream& outputFile)
{
	int r, g, b;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			auto filloutAmount = (sqrt(x * x + y * y) / sqrt(m_width * m_width + m_height * m_height));
			r = g = b = static_cast<int>(filloutAmount * Constants::RGB_MAX);
			outputFile << r << ' ' << g << ' ' << b << std::endl;
		}
	}
}

bool ImageGenerator::generateImage()
{
	std::ofstream outputFile(Constants::OUTPUT_FILE_NAME);
	if (!outputFile.is_open())
	{
		std::cout << "Something went wrong! Couldn`t open file" << std::endl;
		return false;
	}
	
	// .ppm format specifications:
	outputFile << Constants::BIN_FORMAT << std::endl;
	outputFile << m_width << ' ' << m_height << std::endl;
	outputFile << Constants::RGB_MAX << std::endl;

	setPixels(outputFile);
	outputFile.close();
	return true;
}