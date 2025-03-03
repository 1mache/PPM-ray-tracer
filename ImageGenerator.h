#pragma once
#include <fstream>
#include <iostream>
#include <math.h>
#include <random>
#include "Vec3.h"
#include "Camera.h"
#include "Ray.h"
#include "IHitable.h"
#include "HitableSet.h"
#include "Sphere.h"
#include "Config.h"
#include "Dimensions.h"

class ImageGenerator
{		
	// how many ray bounces we allow
	static constexpr uint8_t MAX_RAY_BOUNCES = 50;
	static constexpr float T_MIN = 0.001f;
	static constexpr float T_MAX = FLT_MAX;

	const Dimensions m_screenSize;
	// Wigth to Height ratio
	float m_aspectRatio;
	
	const Camera m_camera;

	// random number generator
	std::random_device m_rd;  // get a random seed from the OS
	std::mt19937 m_generator = std::mt19937(m_rd()); // initialize PRNG with the seed
	std::uniform_real_distribution<float> m_distribution{0.0f, 1.0f}; // initialize distribution
	float random0to1()
	{
		return m_distribution(m_generator);
	}

	const uint8_t m_antialiasingPrecision = 10; // should be 0 if turned off

	const HitableSet& m_world;

	void setPixels(std::ofstream& outputFile);
	// returns color for the given pixel 
	Vec3 calcColor(const Dimensions& screenPoint, const Vec3& viewportRefPoint, bool randomize = false);
	// returns color based on what the ray hit
	Vec3 colorByRay(const Ray& ray, int bounceCounter = 0);
	// same as calcColor but with antialiasing
	Vec3 calcAvgColor(const Dimensions& screenPoint, const Vec3& viewportRefPoint);
	Vec3 gammaCorrection(const Vec3& inputPixel)
	{
		// raises input to the power of 1/2
		return { sqrtf(inputPixel.x()), sqrtf(inputPixel.y()), sqrtf(inputPixel.z()) };
	}
	// generates a random vector inside the unit sphere
	Vec3 randomInUnitSphere();
	void writeRgbValue(std::ofstream& outFile, const Vec3& rgb);
	Vec3 bgPixelColor(const Ray& ray);
public:
	ImageGenerator(const Dimensions& screenSize, float FOV, const HitableSet& world,
		const Vec3& camPosition = { 0,0,0 }, float viewportDist = 1);

	bool generateImage();
};