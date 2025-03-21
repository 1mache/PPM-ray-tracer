#pragma once
#include "ppmRT.h"

class Camera
{
	const Dimensions m_screenSize;
	// how far the viewport is from the camera (to the Z negative direction)
	float m_viewportDist;
	// the angle between the TOP and BOTTOM edges of the viewport
	float m_FOV; // (in radians)

	Vec3 m_lookfrom; // camera position
	Vec3 m_lookat; // what the camera is facing
	static constexpr Vec3 V_UP = { 0,1,0 }; // absolute up direction, relative to camera
	Vec3 m_u, m_v, m_w; // basis of the viewport plane

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
	explicit Camera(
		   const Dimensions& screenSize,
		   const Vec3& position,
		   const Vec3& lookat,
	 	   float FOV);

	Vec3 position() const { return m_lookfrom; }
	float viewportWidth() const { return m_viewportWidth; };
	float viewportHeight() const { return m_viewportHeight; };

	// returns ray from camera to point in viewport
	Ray getRay(const Vec3& viewportPoint) const
	{
		return Ray(m_lookfrom, viewportPoint - m_lookfrom);
	}

	// transformation pixel(x,y) -> pixels center in viewport
	Vec3 screenToViewportPos(const Dimensions& pixelCords) const;
};

