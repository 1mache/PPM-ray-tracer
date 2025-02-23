#pragma once
#include "Constants.h"
#include "Vec3.h"

class Ray
{
	Vec3 m_origin;
	Vec3 m_direction;

public:
	Ray() = default;
	Ray(const Vec3& origin, const Vec3& direction)
		:m_origin(origin), m_direction(direction) {};

	Vec3 getOrigin() const { return m_origin; }
	Vec3 getDirection() const { return m_direction; }
	Vec3 getNormalizedDirection() const { return m_direction.normalized(); }

	// ray = origin + t*direction. 
	// gets the point with given t
	Vec3 pointByParam(float t)
	{
		return m_origin + m_direction * t;
	}
};

