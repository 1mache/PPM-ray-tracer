#include "ImageGenerator.h"

ImageGenerator::ImageGenerator(dimension_t width, dimension_t height, float FOV, const HitableSet& world, 
								const Vec3& camPosition, float viewportDist)
	: m_screenHeight(height), m_screenWidth(width), m_world(world),
	  m_aspectRatio(float(m_screenWidth) / float(m_screenHeight)),
	  m_camera(camPosition, FOV, viewportDist ,m_aspectRatio)
{}

void ImageGenerator::setPixels(std::ofstream& outputFile)
{
	// going from low left up and right
	for (int y = m_screenHeight-1; y >=0; y--)
	{
		for (int x = 0; x < m_screenWidth; x++)
		{
			// times rgbMax to translate 0-1 values to 0-255 values
			Vec3 rgb = calcAvgColor(x, y) * Constants::RGB_MAX;
			writeRgbValue(outputFile, rgb);
		}
	}
}

Vec3 ImageGenerator::calcColor(int screenX, int screenY, bool randomize)
{
	float xRatio, yRatio;

	yRatio = (float(screenY)) / (m_screenHeight - 1);
	xRatio = (float(screenX)) / (m_screenWidth - 1);

	if(randomize) 
	{
		// add random offsets if randomization was requested
		yRatio += random0to1() / (m_screenHeight - 1);
		xRatio += random0to1() / (m_screenWidth - 1);
	}
	
	Ray ray = m_camera.getRay(xRatio, yRatio);
	return colorByRay(ray);
}

Vec3 ImageGenerator::colorByRay(const Ray& ray, int bounceCounter)
{
	HitRecord rec = {};
	float reflectionAmount = 0.5f;
	if (m_world.isHit(ray, T_MIN, FLT_MAX, rec))
	{
		if(bounceCounter < MAX_RAY_BOUNCES)
		{
			// we`re looking at a sphere around our hit point
			Vec3 hitSphereCenter = rec.hitPoint + rec.surfaceNormal;
			Vec3 randomInHitSphere = randomInUnitSphere() + hitSphereCenter;
			return reflectionAmount * colorByRay(Ray(rec.hitPoint, randomInHitSphere - rec.hitPoint), bounceCounter + 1);
		}
		return Vec3(0,0,0); // return black if the recursion depth is too big
	}
	else
		return bgPixelColor(ray);
}

Vec3 ImageGenerator::calcAvgColor(int screenX, int screenY)
{
	HitRecord rec = {};
	Vec3 rgb = { 0,0,0 };

	for (int i = 0; i < m_antialiasingPrecision - 1; i++)
	{
		rgb += calcColor(screenX, screenY, true);
	}

	// one time with no random in case there is no antialiasing
	rgb += calcColor(screenX, screenY);
	
	if(m_antialiasingPrecision > 0)
		rgb /= m_antialiasingPrecision; // divide by number of simulations => get average
	
	return rgb;
}

Vec3 ImageGenerator::randomInUnitSphere()
{
	Vec3 v;
	do
	{
		// generate a vector with components 0 to 1. Transform so components are -1 to 1
		v = 2 * Vec3(random0to1(), random0to1(), random0to1()) - Vec3(1,1,1);
	} while (v.squaredMagnitude() >= 1); //repeat until we get something inside the sphere

	return v;
}

void ImageGenerator::writeRgbValue(std::ofstream& outFile, const Vec3& rgb)
{
	const float rgbMax = float(Constants::RGB_MAX);
	// clamp the values between 255 and 0
	int r = static_cast<int>(std::min(std::max(rgb.x(), 0.0f), rgbMax));
	int g = static_cast<int>(std::min(std::max(rgb.y(), 0.0f), rgbMax));
	int b = static_cast<int>(std::min(std::max(rgb.z(), 0.0f), rgbMax));
	
	outFile << r << ' ' << g << ' ' << b << std::endl;
}

Vec3 ImageGenerator::bgPixelColor(const Ray& ray)
{
	// gradient based on y coordinate:
	// we know that direction is normalized => -1 <= y <= 1
	// so +1 and /2 gives value in between 0 and 1 therefore gradient
	float t = (ray.normalizedDirection().y() + 1.0f) / 2;
	return (1.0f - t) * Constants::WHITE_COLOR + t * Constants::BG_COLOR_FULL; // lerp bg color
}

bool ImageGenerator::generateImage()
{
	std::ofstream outputFile(Constants::PPM_OUTPUT_FILE_NAME);
	if (!outputFile.is_open())
	{
		std::cout << "Something went wrong! Couldn`t open file" << std::endl;
		return false;
	}
	
	// .ppm file specifications:
	outputFile << Constants::PPM_FORMAT << std::endl;
	outputFile << m_screenWidth << ' ' << m_screenHeight << std::endl;
	outputFile << Constants::RGB_MAX << std::endl;

	setPixels(outputFile);
	outputFile.close();
	return true;
}