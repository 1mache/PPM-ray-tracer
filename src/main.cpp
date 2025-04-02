#include "ppmRT.h"
#include "ImageGenerator.h"
#include "Materials.h"
#include "SphereSpawner.h"

int main(int argc, char* argv[])
{
	auto greenishAlbedo = Vec3(0.5f, 0.7f, 0.2f);
	auto greenishMatte = std::make_shared<Lambertian>(greenishAlbedo);
	
	using rng = Utils::RNG;
	Interval posInterval(-5.0f, 5.0f);
	Interval radiusInterval(0.1f, 0.5f);
	std::vector<IHitable*> spheres(51);
	SphereSpawner spawner;

	for(int i = 0; i < 50; i++)
	{
		spheres[i] = spawner.spawnRandomSphere(posInterval, radiusInterval);
	}

	spheres[50] = new Sphere({ 0.0f, -100.5f,  -2.0f }, 100.0f, greenishMatte); // ground
	HitableSet world(std::move(spheres));

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