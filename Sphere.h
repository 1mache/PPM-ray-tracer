#pragma once
#include "Vec3.h"

class Sphere
{
	Vec3 m_center;
	float m_radius;

public:
	Sphere(Vec3 center, float radius):m_center(center), m_radius(radius){}

	Vec3 center() const { return m_center; }
	float radius() const { return m_radius; }
};