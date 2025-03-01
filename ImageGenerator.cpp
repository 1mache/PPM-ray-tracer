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
			Vec3 rgb = avgColor(x, y) * Constants::RGB_MAX;
			writeRgbValue(outputFile, rgb);
		}
	}
}

Vec3 ImageGenerator::calcColor(int screenX, int screenY, float randomComponent)
{
	float yRatio = (float(screenY) + randomComponent)/ (m_screenHeight - 1), 
		xRatio = (float(screenX) + randomComponent) / (m_screenWidth - 1);
	
	Ray ray = m_camera.getRay(xRatio, yRatio);
	HitRecord rec = {};
	if (m_world.isHit(ray, 0.0f, FLT_MAX, rec))
		// we know the normal contains values between -1 and 1 so we convert it to values between 0 and 1
		return (rec.surfaceNormal + Vec3(1.0, 1.0, 1.0)) / 2;
	else
		return bgPixelColor(ray);
}

Vec3 ImageGenerator::avgColor(int screenX, int screenY)
{
	HitRecord rec = {};
	Vec3 rgb = { 0,0,0 };

	for (int i = 0; i < m_antialiasingPrecision - 1; i++)
	{
		float randomComponent = m_distribution(m_generator);
		rgb += calcColor(screenX, screenY, randomComponent);
	}

	// one time with no random in case there is no antialiasing
	rgb += calcColor(screenX, screenY);
	
	if(m_antialiasingPrecision > 0)
		rgb /= m_antialiasingPrecision; // divide by number of simulations => get average
	
	return rgb;
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