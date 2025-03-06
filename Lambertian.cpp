#include "Lambertian.h"

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec,
	Vec3& out_attenuation, Ray& out_scattered) const
{
	Vec3 scatterDirection = rec.surfaceNormal + RNG::randomOnUnitSphere();
	
	// case that randomOnUnitSphere is -rec.surfaceNormal
	if (scatterDirection.nearZero())
		scatterDirection = rec.surfaceNormal;

	out_attenuation = m_albedo; // how much of the color gets reflected

	out_scattered = Ray(rec.hitPoint, scatterDirection);
	return true;
}