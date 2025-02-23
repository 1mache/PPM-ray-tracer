#pragma once

namespace Constants
{
	constexpr size_t IMG_WIDTH = 600;
	constexpr size_t IMG_HEIGHT = 400;

	constexpr const char* OUTPUT_FILE_NAME = "output.ppm";

	// Binary format of the PPM file
	// from https://en.wikipedia.org/wiki/Netpbm#File_formats "P3" means this is a RGB color image in ASCII
	constexpr const char* BIN_FORMAT = "P3";
}