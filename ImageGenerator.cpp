#include "ImageGenerator.h"

ImageGenerator::ImageGenerator(dimension_t width, dimension_t height, float _FOV, const Vec3& _camPosition, float _viewportDist)
	: screenHeight(height), screenWidth(width), FOV(_FOV), // required
	camPosition(_camPosition), viewportDist(_viewportDist) // optional
{
	aspect_ratio = float(screenWidth) / float(screenHeight);
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

	HitableSet world = { new Sphere({ 0,0,-2.0f }, 0.5f) , 
		new Sphere({0, -100.5f, -2.0f}, 100.0f) };
	
	// going from low left up and right
	for (int y = screenHeight-1; y >=0; y--)
	{
		for (int x = 0; x < screenWidth; x++)
		{
			// ratio of current x/y to max x/y
			float yRatio = float(y) / (screenHeight - 1), xRatio = float(x) / (screenWidth - 1);
			// using the ratio translate screen point to viewport point
			Vec3 viewportPoint = lowLeftCorner + xRatio * horizontal + yRatio * vertical;
			
			// cast ray from cam position to the point we calculated
			Ray ray(camPosition, viewportPoint);
			
			Vec3 rgb;
			HitRecord rec = {};
			if(world.isHit(ray, 0.0f, FLT_MAX, rec))
			{
				rgb = (rec.surfaceNormal + Vec3(1.0,1.0,1.0))/2 * Constants::RGB_MAX;
			}
			else
			{
				// get rgb fractions and translate them to 0-255
				 rgb = bgPixelColor(ray) * Constants::RGB_MAX;
			}
			writeRgbValue(outputFile, rgb);
		}
	}
}

void ImageGenerator::writeRgbValue(std::ofstream& outFile, const Vec3& rgb)
{
	const float rgbMax = Constants::RGB_MAX;
	// clamp the values between 255 and 0
	int r = std::min( std::max(rgb.x(), 0.0f), rgbMax);
	int g = std::min(std::max(rgb.y(), 0.0f), rgbMax);
	int b = std::min(std::max(rgb.z(), 0.0f), rgbMax);
	
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
	outputFile << screenWidth << ' ' << screenHeight << std::endl;
	outputFile << Constants::RGB_MAX << std::endl;

	setPixels(outputFile);
	outputFile.close();
	return true;
}