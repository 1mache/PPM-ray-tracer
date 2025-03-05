#pragma once
#include "Vec3.h"
#include "Dimensions.h"

// general program configurations 
namespace Config
{
	constexpr Dimensions SCREEN_SIZE = {600, 400};

	// Max rgb value
	constexpr int RGB_MAX = 255;

	constexpr const char* PPM_OUTPUT_FILE_NAME = "output.ppm";
	constexpr const char* BMP_OUTPUT_FILE_NAME = "output.bmp";

	// Format of the PPM file
	// from https://en.wikipedia.org/wiki/Netpbm#File_formats "P3" means this is a RGB color image in ASCII
	constexpr const char* PPM_FORMAT = "P3";
}