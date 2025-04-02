#pragma once
#include "Vec3.h"
#include "Dimensions.h"

// general program configurations 
namespace Constants
{
	constexpr const char* PPM_OUTPUT_FILE_NAME = "output.ppm";
	constexpr const char* BMP_OUTPUT_FILE_NAME = "output.bmp";

	constexpr float GLASS_REFRACTION = 1.52f;

	// ==================DONT TOUCH==================
	// Max rgb value
	constexpr int RGB_MAX = 255;
	// Format of the PPM file
	// from https://en.wikipedia.org/wiki/Netpbm#File_formats "P3" means this is a RGB color image in ASCII
	constexpr const char* PPM_FORMAT = "P3";
}