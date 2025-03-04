#include "ppmRT.h"
#include "ImageGenerator.h"

int main(int argc, char* argv[])
{
	// 90 degree FOV for now, which is pi/2 rad
	float FOVrad = float(M_PI / 2);

	HitableSet world = { new Sphere({ -1.0f,0.0f,-2.0f }, 0.5f) , new Sphere({0.0f, -100.5f, -2.0f}, 100.0f) };

	ImageGenerator generator(Config::SCREEN_SIZE, FOVrad, world);
	
	if (generator.generateImage())
	{
		std::cout << "Great success!\n";
		std::cout << "Creating a .bmp file ... \n";
		if (Utils::ppmToBmp(Config::PPM_OUTPUT_FILE_NAME, Config::BMP_OUTPUT_FILE_NAME))
		{
			std::cout << "Great success!\n";
		}
		else
			std::cout << "Failed. Terminating\n";
	}
	else
		std::cout << "Failed. Terminating\n";

	return 0;
}