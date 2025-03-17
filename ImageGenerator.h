#pragma once
#include <iomanip>
#include <fstream>
#include <thread>
#include <atomic>
#include <mutex>
#include "ppmRT.h"
#include "Camera.h"
#include "IHitable.h"
#include "HitableSet.h"
#include "Sphere.h"

class ImageGenerator
{
	using RNG = Utils::RNG;

	static constexpr uint8_t RGB_MAX = 255;
	// color of the background
	static constexpr Vec3 BG_COLOR_FULL = { 0.2f, 0.6f, 1.0f };
	// how many ray bounces we allow
	static constexpr uint8_t MAX_RAY_BOUNCES = 25;
	static constexpr Interval T_INTERVAL = { 0.001f, FLT_MAX };
	static constexpr uint8_t NUM_OF_THREADS = 8;
	static constexpr uint8_t DEFAULT_AA_PRECISION = 10;

	// contains rgb values 0 - 1
	using pixelLine = std::vector<Vec3>;
	struct ImageLine
	{
		pixelLine& pixelData;
		Dimensions::dimension_t id; 
	};

private:
	// lines of rgb values
	std::vector<pixelLine> m_image;

	std::atomic<Dimensions::dimension_t> m_linesLeft;
	std::mutex clog_mutex; // mutex for std::clog

	const Dimensions m_screenSize;
	const Camera& m_camera;
	const HitableSet& m_world;

	const uint8_t m_antialiasingPrecision; // 0 to turn off

private:
	// write rgb values to m_image
	void setPixels();
	// function for threads. starting at line start, process every step-th line.
	void processLines(Dimensions::dimension_t start, Dimensions::dimension_t step);
	// processes a single line
	void processLine(const ImageLine& line);
	// same as calcColor but with antialiasing
	Vec3 calcAvgColor(const Dimensions& screenPoint);
	// returns color for the given pixel 
	Vec3 calcColor(const Dimensions& screenPoint, bool randomize = false);
	// returns color based on what the ray hit
	Vec3 colorByRay(const Ray& ray, int bounceCounter = 0);
	
	Vec3 gammaCorrection(const Vec3& inputPixel)
	{
		// raises input to the power of 1/2
		return { sqrtf(inputPixel.x()), sqrtf(inputPixel.y()), sqrtf(inputPixel.z()) };
	}
	// takes color values 0-1 in m_image and writes them as 0-255 to a file
	void writeRgbValues(std::ofstream& outFile);
	Vec3 bgPixelColor(const Ray& ray);

public:
	explicit ImageGenerator(
		const HitableSet& world,
		const Camera& camera,
		uint8_t antialiasingPrecision = DEFAULT_AA_PRECISION
	);

	bool generateImage();
};