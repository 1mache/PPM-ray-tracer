#include "ImageGenerator.h"

void ImageGenerator::setPixels(std::ofstream& outputFile)
{

}

bool ImageGenerator::generateImage()
{
	std::ofstream outputFile(Constants::OUTPUT_FILE_NAME);
	if (!outputFile.is_open())
	{
		std::cout << "Something went wrong! Couldn`t open file" << std::endl;
		return false;
	}

	outputFile << Constants::BIN_FORMAT << std::endl;
	outputFile << Constants::IMG_WIDTH << ' ' << Constants::IMG_HEIGHT << std::endl;

	setPixels(outputFile);
	outputFile.close();
	return true;
}