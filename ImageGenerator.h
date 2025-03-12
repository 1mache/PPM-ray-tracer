#pragma once
#include <fstream>
#include "ppmRT.h"
#include "Camera.h"
#include "IHitable.h"
#include "HitableSet.h"
#include "Sphere.h"

class ImageGenerator
{
	using RNG = Utils::RNG;

	// color of the background
	static constexpr Vec3 BG_COLOR_FULL = { 0.2f, 0.6f, 1.0f };
	// how many ray bounces we allow
	static constexpr uint8_t MAX_RAY_BOUNCES = 25;
	static constexpr Interval T_INTERVAL = { 0.001f, FLT_MAX };

	const Dimensions m_screenSize;
	
	const Camera& m_camera;

	const uint8_t m_antialiasingPrecision = 10; // 0 to turn off

	const HitableSet& m_world;

	void setPixels(std::ofstream& outputFile);
	// returns color for the given pixel 
	Vec3 calcColor(const Dimensions& screenPoint, bool randomize = false);
	// returns color based on what the ray hit
	Vec3 colorByRay(const Ray& ray, int bounceCounter = 0);
	// same as calcColor but with antialiasing
	Vec3 calcAvgColor(const Dimensions& screenPoint);
	Vec3 gammaCorrection(const Vec3& inputPixel)
	{
		// raises input to the power of 1/2
		return { sqrtf(inputPixel.x()), sqrtf(inputPixel.y()), sqrtf(inputPixel.z()) };
	}
	// expects color values 0-1 and writes them as 0-255 to a file
	void writeRgbValue(std::ofstream& outFile, const Vec3& rgb);
	Vec3 bgPixelColor(const Ray& ray);

public:
	explicit ImageGenerator(
		const Dimensions& screenSize, 
		const HitableSet& world,
		const Camera& camera
	);

	bool generateImage();
};