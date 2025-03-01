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
#include "Constants.h"

class ImageGenerator
{
	using dimension_t = Constants::dimension_t;

	const dimension_t m_screenWidth, m_screenHeight;
	// Wigth to Height ratio
	float m_aspectRatio;
	
	Camera m_camera;

	// random number generator
	std::random_device m_rd;  // get a random seed from the OS
	std::mt19937 m_generator = std::mt19937(m_rd()); // initialize PRNG with the seed
	std::uniform_real_distribution<float> m_distribution{0.0f, 1.0f}; // initialize distribution

	const uint8_t m_antialiasingPrecision = 100; // should be 0 if turned off

	HitableSet m_world;

	void setPixels(std::ofstream& outputFile);
	Vec3 calcColor(int screenX, int screenY, float randomComponent = 0);
	Vec3 avgColor(int screenX, int screenY);
	void writeRgbValue(std::ofstream& outFile, const Vec3& rgb);
	Vec3 bgPixelColor(const Ray& ray);
public:
	ImageGenerator(dimension_t width, dimension_t height, float FOV, const HitableSet& world,
		const Vec3& camPosition = { 0,0,0 }, float viewportDist = 1);

	bool generateImage();
};