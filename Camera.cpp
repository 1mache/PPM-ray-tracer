#include "Camera.h"

Camera::Camera(const Vec3& position, float FOV, float viewportDist, float screenAspectRatio):
	m_position(position), m_FOV(FOV), m_viewportDist(viewportDist)
{
	// height calculated from FOV using famous formula
	m_viewportHeight = 2 * (tan(FOV / 2) * viewportDist); // see explanation in /theory
	// width is calculated from height using aspect ratio
	m_viewportWidth = m_viewportHeight * screenAspectRatio;

	m_horizontal = Vec3(m_viewportWidth, 0, 0);
	m_vertical = Vec3(0, m_viewportHeight, 0);
	// y positive is up, x positive is right
}

Vec3 Camera::screenToViewportPos(const Dimensions& pixelCords) const
{
	// I use the top left corner as reference point
	Vec3 topLeftViewportCorner = Vec3(-m_viewportWidth / 2, m_viewportHeight / 2, viewportZ());

	Vec3 downBy = m_vertical * (float(pixelCords.height) / (Config::SCREEN_SIZE.height - 1));
	Vec3 rightBy = m_horizontal * (float(pixelCords.width) / (Config::SCREEN_SIZE.width - 1));

	return topLeftViewportCorner - downBy + rightBy;
}
