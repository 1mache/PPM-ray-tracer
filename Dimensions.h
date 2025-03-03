#pragma once

struct Dimensions
{
	// type for image dimensions
	typedef uint16_t dimension_t;

	const dimension_t width, height;
	constexpr Dimensions(dimension_t _width, dimension_t _height) : width(_width), height(_height) {}
};

