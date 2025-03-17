#pragma once
#include "Constants.h"
#include "Vec3.h"

// ray = origin + t*direction. 
class Ray
{
	Vec3 m_origin;
	Vec3 m_direction;

public:
	Ray() = default;
	Ray(const Vec3& origin, const Vec3& direction)
		:m_origin(origin), m_direction(direction){};

	Vec3 origin() const { return m_origin; }
	Vec3 direction() const { return m_direction; }

	// gets the point with given t
	// !!Direction here is not normalized!!
	Vec3 pointByParam(float t) const
	{
		return m_origin + (m_direction * t);
	}
};

