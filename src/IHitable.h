#pragma once
#include "ppmRT.h"

class Material;

struct HitRecord
{
	std::shared_ptr<Material> material;
	Vec3 hitPoint;
	Vec3 surfaceNormal;
	float t;
	bool frontFace; // whether the normal is pointing "out" of the object
};

class IHitable
{
public:
	virtual ~IHitable() = default;
	virtual bool isHit(
		const Ray& ray, 
		Interval tInterval, 
		HitRecord& out_record
	) const = 0;
};