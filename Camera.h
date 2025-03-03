#pragma once
#include "Vec3.h"
#include "Ray.h"

class Camera
{
	// how far the viewport is from the camera (to the Z negative direction)
	const float m_viewportDist;
	// the angle between the TOP and BOTTOM edges of the viewport
	const float m_FOV; // (in radians)

	Vec3 m_position;
	// the width and height of the "window" we're looking at the world through
	// calculated using FOV
	float m_viewportWidth, m_viewportHeight;

	// positive horizontal and vertical viewport dimensions as vectors
	Vec3 m_horizontal, m_vertical;
public:
	Camera(const Vec3& position, float FOV, float viewportDist, float screenAspectRatio);

	Vec3 position() const { return m_position; }
	float viewportWidth() const { return m_viewportWidth; };
	float viewportHeight() const { return m_viewportHeight; };
	// returns the viewports z position
	float viewportZ() const { return m_position.z() - m_viewportDist; }

	// returns ray from camera to point in viewport
	Ray getRay(const Vec3& viewportPoint) const
	{
		return Ray(m_position, viewportPoint - m_position);
	}

	// transformation pixel(x,y) -> point in viewport
	Vec3 screenToViewportPos(const Dimensions& pixelCords) const;
};

