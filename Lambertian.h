#pragma once
#include "Material.h"

class Lambertian: public Material
{
	using RNG = Utils::RNG;

	// how much of every color gets reflected
	Vec3 m_albedo;
public:
	Lambertian(const Vec3& albedo) : m_albedo(albedo) {}

	virtual bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const override;
};

