#pragma once
#include "Ray.h"
#include "Vec3.h"

struct HitRecord
{
	float t;
	Vec3 hitPoint;
	Vec3 surfaceNormal;
};

class IHitable
{
public:
	~IHitable() {};
	virtual bool isHit(const Ray& ray, float tMin, float tMax, HitRecord& out_record) const = 0;
};