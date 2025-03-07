#include "ppmRT.h"
#include "ImageGenerator.h"
#include "AllMaterials.h"

int main(int argc, char* argv[])
{
	auto reddishAlbedo =  Vec3(0.8f, 0.3f, 0.3f);
	auto greenishAlbedo = Vec3(0.5f, 0.7f, 0.2f);
	auto purpleAlbedo =   Vec3(0.9f, 0.4f, 0.9f);
	auto metalAlbedo =    Vec3(1.0f, 0.8f, 1.0f);

	auto reddishMatte =  std::make_shared<Lambertian>(reddishAlbedo);
	auto greenishMatte = std::make_shared<Lambertian>(greenishAlbedo);
	auto purpleMatte =   std::make_shared<Lambertian>(purpleAlbedo);
	auto fuzzyMetal =    std::make_shared<Metal>(metalAlbedo, 0.5f);
	auto clearMetal =    std::make_shared<Metal>(metalAlbedo, 0.0f);

	HitableSet world = { 
		new Sphere({  0.0f,    0.0f,  -2.0f },   0.5f, reddishMatte),
		new Sphere({ -1.25f,   1.0f,  -2.0f },   0.25f, purpleMatte),
		new Sphere({ -1.5f,    0.25f, -2.0f },   0.75f, fuzzyMetal),
		new Sphere({  1.5f,    0.5f,  -2.0f },   1.0f, clearMetal),
		new Sphere({  0.0f, -100.5f,  -2.0f }, 100.0f, greenishMatte),
	};

	ImageGenerator generator(Config::SCREEN_SIZE, world);
	
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