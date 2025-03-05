#pragma once
#include "IHitable.h"

class Material
{

public:
	virtual ~Material() = default;
	virtual bool scatter(
		const Ray& rayIn, const HitRecord& rec, Vec3& out_attenuation, Ray& out_scattered
	) const = 0;
};

