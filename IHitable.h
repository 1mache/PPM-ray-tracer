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
	// max and min ray multiplier
	static constexpr float T_MIN = 0, T_MAX = FLT_MAX;
public:
	~IHitable() {};
	virtual bool isHit(const Ray& ray, HitRecord& record) = 0;
};