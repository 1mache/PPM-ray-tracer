#include <iostream>
#include <fstream>

#include "Constants.h"

void setPixels(std::ofstream& outputFile)
{
	std::cout << "Generating...";
}

bool generateImage()
{
	std::ofstream outputFile(Constants::OUTPUT_FILE_NAME);
	if(!outputFile.is_open())
	{
		std::cout << "Something went wrong! Couldn`t open file";
		return false;
	}

	outputFile << Constants::BIN_FORMAT << std::endl;
	outputFile << Constants::IMG_WIDTH << ' ' << Constants::IMG_HEIGHT << std::endl;

	setPixels(outputFile);
	outputFile.close();
}
int main(int argc, char* argv[])
{
	generateImage();
	std::cout << "Done!";
}