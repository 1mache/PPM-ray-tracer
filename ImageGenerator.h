#pragma once
#include <fstream>
#include <iostream>
#include <math.h>
#include "Vec3.h"
#include "Ray.h"
#include "Constants.h"

class ImageGenerator
{
	const float screenWidth, screenHeight;
	// Wigth to Height ratio
	float aspect_ratio;
	
	// the angle between the TOP and BOTTOM edges of the viewport
	const float FOV; // in radians
	
	Vec3 camPosition;

	// how far the viewport is from the camera (to the Z negative direction)
	const float viewportDist;
	// the width and height of the "window" we're looking at the world through
	// calculated using FOV
	float viewportWidth, viewportHeight; 


	void setPixels(std::ofstream& outputFile);
	void writeRgbValue(std::ofstream& outFile, const Vec3& rgb);
	Vec3 bgPixelColor(const Ray& ray);
public:
	ImageGenerator(size_t width, size_t height, float _FOV,
		const Vec3& _camPosition = { 0,0,0 }, float _viewportDist = 1);

	bool generateImage();
};