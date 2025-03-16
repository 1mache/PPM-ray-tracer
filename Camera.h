#pragma once
#include "ppmRT.h"

class Camera
{
	// how far the viewport is from the camera (to the Z negative direction)
	float m_viewportDist;
	// the angle between the TOP and BOTTOM edges of the viewport
	float m_FOV; // (in radians)

	Vec3 m_lookfrom;
	Vec3 m_lookat;
	static constexpr Vec3 V_UP = { 0,1,0 }; // absolute up direction, relative to camera
	Vec3 m_u, m_v, m_w; // basis of the camera frame

	// the width and height of the "window" we're looking at the world through
	// calculated using FOV
	float m_viewportWidth, m_viewportHeight;
	
	// viewport pixel size (z is 0) 
	Vec3 m_pixelSize;

private:
	// translates a given vector from screen basis ({1,0}, {0,1}) to viewport basis (m_u, m_v),
	Vec3 toViewportBasis(const Vec3& vec) const
	{
		// vec`s z cord is ignored, as vec represents vector in screen space
		return m_u * vec.x() + m_v * vec.y();
	}
public:
	Camera(const Vec3& position, const Vec3& lookat, float FOV);

	Vec3 position() const { return m_lookfrom; }
	float viewportWidth() const { return m_viewportWidth; };
	float viewportHeight() const { return m_viewportHeight; };
	// returns the viewports z position
	float viewportZ() const { return m_lookfrom.z() - m_viewportDist; }

	// returns ray from camera to point in viewport
	Ray getRay(const Vec3& viewportPoint) const
	{
		return Ray(m_lookfrom, viewportPoint - m_lookfrom);
	}

	// transformation pixel(x,y) -> pixels center in viewport
	Vec3 screenToViewportPos(const Dimensions& pixelCords) const;
};

