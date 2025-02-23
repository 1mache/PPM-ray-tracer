#include "ImageGenerator.h"
#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char* argv[])
{
	// 90 degree FOV for now, which is pi/2 rad
	float FOVrad = M_PI / 2;

	ImageGenerator generator(Constants::IMG_WIDTH, Constants::IMG_HEIGHT, FOVrad);
	
	if (generator.generateImage())
		std::cout << "Great success!";
	else
		std::cout << "Failed. Terminating";
}