#include "ImageGenerator.h"

ImageGenerator::ImageGenerator (const Dimensions& screenSize, 
								const HitableSet& world, 
								const Camera& camera)
	: m_screenSize(screenSize), 
	  m_world(world),
	  m_camera(camera),
	  m_image(screenSize.height, std::vector<Vec3>(screenSize.width))
{
	m_linesLeft = m_screenSize.height;
}

void ImageGenerator::setPixels()
{
	std::vector<std::thread> threads(NUM_OF_THREADS);
	for (uint8_t i = 0; i < NUM_OF_THREADS; i++)
	{
		threads[i] = std::thread(&ImageGenerator::processLines, this, i, NUM_OF_THREADS);
	}

	for (auto& thread : threads)
	{
		thread.join();
	}
}

void ImageGenerator::processLines(Dimensions::dimension_t start, Dimensions::dimension_t step)
{
	for (Dimensions::dimension_t y = start; y < m_screenSize.height; y += step)
	{
		ImageLine line = { m_image[y] , y };
		processLine(line);
	}
}

void ImageGenerator::processLine(const ImageLine& line)
{
	for (Dimensions::dimension_t x = 0; x < m_screenSize.width; x++)
	{
		Vec3 rgb = calcAvgColor(Dimensions(x, line.id));
		rgb = gammaCorrection(rgb);
		
		line.pixelData[x] = rgb;
	}
	
	m_linesLeft--;
	std::lock_guard<std::mutex> clogLock(clog_mutex);
	std::clog << "Lines left: " << m_linesLeft << std::endl;
}

Vec3 ImageGenerator::calcAvgColor(const Dimensions& screenPoint)
{
	Vec3 rgb = { 0,0,0 };

	for (uint8_t i = 0; i < m_antialiasingPrecision - 2; i++)
	{
		rgb += calcColor(screenPoint, true); // randomize origin of ray
	}

	// one time with no random in case there is no antialiasing
	rgb += calcColor(screenPoint);

	if (m_antialiasingPrecision > 0)
		rgb /= m_antialiasingPrecision; // divide by number of simulations => get average

	return rgb;
}

Vec3 ImageGenerator::calcColor(const Dimensions& screenPoint, bool randomize)
{
	Vec3 viewportPoint = m_camera.screenToViewportPos(screenPoint);

	if(randomize) 
	{
		// add random offset if randomization was requested
		Vec3 offset = { (RNG::random0to1() - 0.5f)/ (m_screenSize.height - 1), 
						(RNG::random0to1() - 0.5f)/ (m_screenSize.width - 1),
						0.0f }; // offset is inside the single viewport pixel borders
		viewportPoint += offset;
	}
	
	Ray ray = m_camera.getRay(viewportPoint);
	return colorByRay(ray);
}

Vec3 ImageGenerator::colorByRay(const Ray& ray, int bounceCounter)
{
	if (bounceCounter >= MAX_RAY_BOUNCES)
		return Vec3(0.0f, 0.0f, 0.0f);

	HitRecord rec = {};
	float reflectionAmount = 0.5f;
	if (m_world.isHit(ray, T_INTERVAL, rec))
	{
		Vec3 attenuation;
		Ray scattered;
		if(rec.material->scatter(ray, rec, attenuation, scattered))
			return attenuation * 
				colorByRay(scattered, bounceCounter + 1);
			
		return Vec3(0.0f, 0.0f, 0.0f); // return black if the material doesnt scatter.
	}
	
	return bgPixelColor(ray);
}

void ImageGenerator::writeRgbValues(std::ofstream& outFile)
{
	std::clog << "Writing to PPM file ... " << std::endl;
	for (auto line : m_image)
	{
		for (auto rgb : line)
		{
			const float rgbMax = float(Config::RGB_MAX);
			// clamp the values between 255 and 0
			int r = static_cast<int>(std::min(std::max(rgb.x() * rgbMax, 0.0f), rgbMax));
			int g = static_cast<int>(std::min(std::max(rgb.y() * rgbMax, 0.0f), rgbMax));
			int b = static_cast<int>(std::min(std::max(rgb.z() * rgbMax, 0.0f), rgbMax));

			outFile << r << ' ' << g << ' ' << b << std::endl;
		}
	}
	std::clog << "Done!" << std::endl;
}

Vec3 ImageGenerator::bgPixelColor(const Ray& ray)
{
	Vec3 whiteColor = { 1.0f, 1.0f, 1.0f };
	Vec3 normalizedRayDirection = ray.direction().normalized();
	// gradient based on y coordinate:
	// we know that direction is normalized => -1 <= y <= 1
	// so +1 and /2 gives value in between 0 and 1 therefore gradient
	float t = (normalizedRayDirection.y() + 1.0f) / 2;
	return ((1.0f - t) * whiteColor + t * BG_COLOR_FULL) * 0.5; // lerp bg color
}

bool ImageGenerator::generateImage()
{
	std::ofstream outputFile(Config::PPM_OUTPUT_FILE_NAME);
	if (!outputFile.is_open())
	{
		std::cout << "Something went wrong! Couldn`t open file" << std::endl;
		return false;
	}
	
	// .ppm file specifications:
	outputFile << Config::PPM_FORMAT << std::endl;
	outputFile << m_screenSize.width << ' ' << m_screenSize.height << std::endl;
	outputFile << Config::RGB_MAX << std::endl;

	setPixels();
	writeRgbValues(outputFile);

	outputFile.close();
	return true;
}