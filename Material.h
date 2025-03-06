#pragma once
#include "IHitable.h"

class Material
{
public:
	virtual ~Material() = default;
	virtual bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const = 0;
};

