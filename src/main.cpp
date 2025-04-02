#include "ppmRT.h"
#include "ImageGenerator.h"
#include "Materials.h"
#include "SphereSpawner.h"

int main(int argc, char* argv[])
{
	auto grayAlbedo = Vec3(0.2f, 0.2f, 0.2f);
	auto floorMaterial = std::make_shared<Lambertian>(grayAlbedo);
	
	using rng = Utils::RNG;
	Interval posInterval(-5.0f, 5.0f);
	Interval radiusInterval(0.1f, 0.5f);
	uint8_t sphereCount = 50;
	std::vector<IHitable*> spheres(sphereCount + 1);
	SphereSpawner spawner;

	for(int i = 0; i < sphereCount; i++)
	{
		spheres[i] = spawner.spawnRandomSphere(posInterval, radiusInterval);
	}

	spheres[sphereCount] = new Sphere({ 0.0f, -100.5f,  -2.0f }, 100.0f, floorMaterial); // ground
	HitableSet world(std::move(spheres));

	auto screenDimensions = Dimensions(800, 600);
    Camera camera = Camera(
		screenDimensions,
		{ -1.0f, 0.8f, 1.0f }, // position
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