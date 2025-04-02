#include "ppmRT.h"
#include "ImageGenerator.h"
#include "Materials.h"

int main(int argc, char* argv[])
{
	auto reddishAlbedo =  Vec3(0.8f, 0.3f, 0.3f);
	auto greenishAlbedo = Vec3(0.5f, 0.7f, 0.2f);
	auto purpleAlbedo =   Vec3(0.9f, 0.4f, 0.9f);
	auto metalAlbedo =    Vec3(1.0f, 0.8f, 1.0f);

	auto reddishMatte  =    std::make_shared<Lambertian>(reddishAlbedo);
	auto greenishMatte =    std::make_shared<Lambertian>(greenishAlbedo);
	auto purpleMatte   =    std::make_shared<Lambertian>(purpleAlbedo);
	auto fuzzyMetal    =    std::make_shared<Metal>(metalAlbedo, 0.5f);
	auto clearMetal    =    std::make_shared<Metal>(metalAlbedo, 0.0f);
	auto glass		   =	std::make_shared<Dielectric>(1.5f);
	auto bubble        =	std::make_shared<Dielectric>(1.0f/1.5f);


	HitableSet world = { 
		new Sphere({  0.0f,    0.0f,  -2.0f },   0.5f, reddishMatte),
		new Sphere({  0.0f,    0.6f,  -1.8f },   0.25f, purpleMatte),
		new Sphere({ -1.5f,    0.25f, -2.0f },   0.75f, glass), // outer glass sphere
		new Sphere({ -1.5f,    0.25f, -2.0f },   0.65f, bubble), // hollow part of air
		new Sphere({  1.5f,    0.5f,  -2.0f },   1.0f, fuzzyMetal),
		new Sphere({  0.0f, -100.5f,  -2.0f }, 100.0f, greenishMatte) // ground,
	};

	auto screenDimensions = Dimensions(800, 600);
    Camera camera = Camera(
		screenDimensions,
		{ 0.0f, 0.0f, 1.0f }, // position
		{ 0.0f, 0.0f, -1.0f }, // direction
		M_PI / 1.5 ); // vertical field of view		

	ImageGenerator generator(screenDimensions ,world, camera);
	
	if (generator.generateImage())
	{
		std::cout << "Great success!\n";
		std::cout << "Creating a .bmp file ... \n";
		if (Utils::ppmToBmp(
				(Utils::getExePath() / Constants::PPM_OUTPUT_FILE_NAME).string(),
				(Utils::getExePath() / Constants::BMP_OUTPUT_FILE_NAME).string())
			)
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