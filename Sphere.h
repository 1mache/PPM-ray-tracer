#pragma once
#include "IHitable.h"

class Sphere : public IHitable
{
	Vec3 m_center;
	float m_radius;

public:
	Sphere(Vec3 center, float radius):m_center(center), m_radius(radius){}

	Vec3 center() const { return m_center; }
	float radius() const { return m_radius; }

	bool isHit(const Ray& ray, float tMin, float tMax, HitRecord& out_record) const override;
};