#pragma once
#include "Config.h"
#include "Vec3.h"

// ray = origin + t*direction. 
class Ray
{
	Vec3 m_origin;
	Vec3 m_direction;
	Vec3 m_normDirection;

public:
	Ray() = default;
	Ray(const Vec3& origin, const Vec3& direction)
		:m_origin(origin), m_direction(direction), m_normDirection(m_direction.normalized()) {};

	Vec3 origin() const { return m_origin; }
	Vec3 direction() const { return m_direction; }
	Vec3 normalizedDirection() const { return m_normDirection; }

	// gets the point with given t
	Vec3 pointByParam(float t) const
	{
		return m_origin + (m_direction * t);
	}
};

