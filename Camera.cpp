#include "Camera.h"

Camera::Camera(const Vec3& position, float FOV, float viewportDist, float screenAspectRatio):
	m_position(position), m_FOV(FOV), m_viewportDist(viewportDist)
{
	// height calculated from FOV using famous formula
	m_viewportHeight = 2 * (tan(FOV / 2) * viewportDist); // see explanation in /theory
	// width is calculated from height using aspect ratio
	m_viewportWidth = m_viewportHeight * screenAspectRatio;
	
	m_pixelSize = Vec3(m_viewportWidth / Config::SCREEN_SIZE.width,
		m_viewportHeight / Config::SCREEN_SIZE.height,
		0.0f);
}

Vec3 Camera::screenToViewportPos(const Dimensions& pixelCords) const
{
	// we need to flip here, (0,0) in screen cords is the top left corner and in our cords its the bottom left one
	Dimensions flippedCords = Dimensions( pixelCords.width , Config::SCREEN_SIZE.height - pixelCords.height); 
	// this is currently the viewports bottomLeft corner and not the pixel center
	Vec3 bottomLeftPixel = Vec3(-m_viewportWidth / 2, -m_viewportHeight / 2, viewportZ());

	bottomLeftPixel += 0.5 * m_pixelSize; // offset it to the center of the pixel

	// the desired pixel's offset *ratio*
	Vec3 pixelOffset = Vec3((float(flippedCords.width) / (Config::SCREEN_SIZE.width - 1)),
							(float(flippedCords.height) / (Config::SCREEN_SIZE.height - 1)),
							0.0f);	

	pixelOffset *= Vec3(m_viewportWidth, m_viewportHeight, 0); // multiply it by viewport dimensions to get the offset

	return bottomLeftPixel + pixelOffset;
}
