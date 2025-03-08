#pragma once
#include "Material.h"

class Dielectric : public Material
{
	float m_refractionIndex;

	Vec3 refract(const Vec3& vIn, const Vec3& normal, float refractionIndexRatio) const;
public:
	Dielectric(float refractionIndex) : m_refractionIndex(refractionIndex)
	{}

	bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const override;
};

