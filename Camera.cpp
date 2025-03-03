#include "Camera.h"

Camera::Camera(const Vec3& position, float FOV, float viewportDist, float screenAspectRatio):
	m_position(position), m_FOV(FOV), m_viewportDist(viewportDist)
{
	// height calculated from FOV using famous formula
	m_viewportHeight = 2 * (tan(FOV / 2) * viewportDist); // see explanation in materials
	// width is calculated from height using aspect ratio
	m_viewportWidth = m_viewportHeight * screenAspectRatio;

	m_horizontal = Vec3(m_viewportWidth, 0, 0);
	m_vertical = Vec3(0, m_viewportHeight, 0);
	// y positive is up, x positive is right
}

Ray Camera::getRay(float xRatio, float yRatio, const Vec3& referencePoint) const
{
	// using the ratio and referencePoint translate screen point to viewport point
	Vec3 viewportPoint = referencePoint + (xRatio * m_horizontal) + (yRatio * m_vertical);

	// cast ray from cam position to the point we calculated
	return Ray(m_position, viewportPoint);
}
