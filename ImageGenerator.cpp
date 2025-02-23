#include "ImageGenerator.h"

ImageGenerator::ImageGenerator(size_t width, size_t height, float _FOV, const Vec3& _camPosition, float _viewportDist)
	: screenHeight(height), screenWidth(width), FOV(_FOV),
	camPosition(_camPosition), viewportDist(_viewportDist) //optional
{
	aspect_ratio = width / height;
	// height calculated from FOV using famous formula
	viewportHeight = 2 * (tan(FOV / 2) * viewportDist); // see image in materials
	// width is calculated from height using aspect ratio
	viewportWidth = viewportHeight * aspect_ratio;
}

void ImageGenerator::setPixels(std::ofstream& outputFile)
{
	const Vec3 horizontal(viewportWidth, 0, 0);
	const Vec3 vertical(0, viewportHeight, 0);

	// think about it: y positive is up, x positive is right
	const Vec3 lowLeftCorner(-viewportWidth/2, -viewportHeight/2, -viewportDist);

	// going from low left up and right
	for (int y = screenHeight-1; y >=0; y--)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			// ratio of current x/y to max x/y
			float yRatio = y / (screenHeight - 1), xRatio = x / (screenWidth - 1);
			// using the ratio translate screen point to viewport point
			Vec3 viewportPoint = lowLeftCorner + xRatio * horizontal + yRatio * vertical;
			
			// cast ray from cam position to the point we calculated
			Ray ray(camPosition, viewportPoint);
			// get rgb fractions and translate them to 0-255
			Vec3 rgb = bgPixelColor(ray) * Constants::RGB_MAX;
			writeRgbValue(outputFile, rgb);
		}
	}
}

void ImageGenerator::writeRgbValue(std::ofstream& outFile, const Vec3& rgb)
{
	const int max = Constants::RGB_MAX;
	// make sure the values are in range
	int r = rgb.x() < max ? int(rgb.x()) : max;
	int g = rgb.y() < max ? int(rgb.y()) : max;
	int b = rgb.z() < max ? int(rgb.z()) : max;
	
	outFile << r << ' ' << g << ' ' << b << std::endl;
}

Vec3 ImageGenerator::bgPixelColor(const Ray& ray)
{
	// gradient based on y coordinate:
	// we know that direction is normalized => -1 <= y <= 1
	// so +1 and times 0.5 gives value in between 0 and 1 therefore gradient
	float t = 0.5f * (ray.getNormalizedDirection().y() + 1.0f);
	return (1.0f - t) * Constants::WHITE_COLOR + t * Constants::BG_COLOR_FULL; // lerp bg color
}


bool ImageGenerator::generateImage()
{
	std::ofstream outputFile(Constants::OUTPUT_FILE_NAME);
	if (!outputFile.is_open())
	{
		std::cout << "Something went wrong! Couldn`t open file" << std::endl;
		return false;
	}
	
	// .ppm format specifications:
	outputFile << Constants::BIN_FORMAT << std::endl;
	outputFile << screenWidth << ' ' << screenHeight << std::endl;
	outputFile << Constants::RGB_MAX << std::endl;

	setPixels(outputFile);
	outputFile.close();
	return true;
}