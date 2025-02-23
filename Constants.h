#pragma once
#include "Vec3.h"

namespace Constants
{
	constexpr size_t IMG_WIDTH = 600;
	constexpr size_t IMG_HEIGHT = 400;

	// Max rgb value
	constexpr size_t RGB_MAX = 255;

	constexpr Vec3 WHITE_COLOR = { 1.0f, 1.0f, 1.0f };
	constexpr Vec3 BG_COLOR_FULL = {0.2f, 0.6f, 1.0f };

	constexpr const char* OUTPUT_FILE_NAME = "output.ppm";

	// Binary format of the PPM file
	// from https://en.wikipedia.org/wiki/Netpbm#File_formats "P3" means this is a RGB color image in ASCII
	constexpr const char* BIN_FORMAT = "P3";
}