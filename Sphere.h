#pragma once
#include "IHitable.h"
#include "Material.h"

class Sphere : public IHitable
{
	Vec3 m_center;
	float m_radius;
	std::shared_ptr<Material> m_material;

public:
	Sphere(Vec3 center, float radius, std::shared_ptr<Material> material)
		:m_center(center), m_radius(radius), m_material(material){}

	Vec3 center() const { return m_center; }
	float radius() const { return m_radius; }

	bool isHit(const Ray& ray, Interval tInterval, HitRecord& out_record) const override;
};