#include "ImageGenerator.h"

int main(int argc, char* argv[])
{
	ImageGenerator generator(Constants::IMG_WIDTH, Constants::IMG_HEIGHT);

	
	if (generator.generateImage())
		std::cout << "Great success!";
	else
		std::cout << "Failed. Terminating";
}