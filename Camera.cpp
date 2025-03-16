#include "Camera.h"

Camera::Camera(const Vec3& position, const Vec3& lookat ,float FOV):
	m_lookfrom(position), m_lookat(lookat), m_FOV(FOV)
{
	float screenAspectRatio = float(Config::SCREEN_SIZE.width) / Config::SCREEN_SIZE.height;

	m_viewportDist = (m_lookfrom - m_lookat).magnitude(); // distance from camera to viewport
	// height calculated from FOV using famous formula
	m_viewportHeight = 2 * (tan(FOV / 2) * m_viewportDist); // see explanation in /theory
	// width is calculated from height using aspect ratio
	m_viewportWidth = m_viewportHeight * screenAspectRatio;
	
	m_pixelSize = Vec3(m_viewportWidth / Config::SCREEN_SIZE.width,
					   m_viewportHeight / Config::SCREEN_SIZE.height,
					   0.0f);

	m_w = (m_lookfrom - m_lookat).normalized();
	m_u = cross(V_UP, m_w).normalized();
	m_v = cross(m_w, m_u); // already unit length
}

Vec3 Camera::screenToViewportPos(const Dimensions& pixelCords) const
{
	// we need to flip here, (0,0) in screen cords is the top left corner and in our cords its the bottom left one
	Dimensions flippedCords = Dimensions( pixelCords.width , Config::SCREEN_SIZE.height - pixelCords.height); 
	
	Vec3 viewportHorizontal = m_viewportHeight * m_v;
	Vec3 viewportVertical   = m_viewportWidth * m_u;

	// this is currently the viewports bottomLeft corner and not the pixel center
	Vec3 bottomLeftPixel =  -viewportVertical / 2 
							-viewportHorizontal / 2 
							-m_viewportDist * m_w;

	bottomLeftPixel += 0.5f * toViewportBasis(m_pixelSize); // offset it to the center of the pixel

	// the desired pixel's offset *ratio*
	Vec3 pixelOffset = Vec3((float(flippedCords.width) / (Config::SCREEN_SIZE.width - 1)),
							(float(flippedCords.height) / (Config::SCREEN_SIZE.height - 1)),
							0.0f);	

	pixelOffset *= Vec3(m_viewportWidth, m_viewportHeight, 0.0f); // multiply it by viewport dimensions to get the offset

	// translate offset to our (m_u , m_v) basis and add the resulting offset to the bottom left corner
	return bottomLeftPixel + toViewportBasis(pixelOffset);
}
