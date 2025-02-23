#include "ImageGenerator.h"
void ImageGenerator::setPixels(std::ofstream& outputFile)
{
	Vec3 rgb;
	float& r = rgb.x();
	float& g = rgb.y();
	float& b = rgb.z();

	Vec3 pixelVector;
	const float screenDiagonal = sqrt(m_width * m_width + m_height * m_height);
	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++)
		{
			pixelVector = Vec3(x,y,0);
			auto filloutAmount = (pixelVector.magnitude() / screenDiagonal);
			rgb = Vec3(1,1,1) * filloutAmount * Constants::RGB_MAX;
			r = 255;
			outputFile << int(r) << ' ' << int(g) << ' ' << int(b) << std::endl;
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