#include "ppmRT.h"
#include "ImageGenerator.h"
#include "Material.h"
#include "Lambertian.h"

int main(int argc, char* argv[])
{
	auto reddishAlbedo = Vec3(0.8, 0.3, 0.3);
	auto greenishAlbedo = Vec3(0.5, 0.8, 0.5);

	std::shared_ptr<Material> reddishMatte = std::make_shared<Lambertian>(reddishAlbedo);
	std::shared_ptr<Material> greenishMatte = std::make_shared<Lambertian>(greenishAlbedo);

	HitableSet world = { new Sphere({ 0.0f,-0.5f,-2.0f }, 0.5f, reddishMatte) ,
		new Sphere({0.0f, -100.5f, -2.0f}, 100.0f, greenishMatte) };

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