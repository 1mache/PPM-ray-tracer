#include "Lambertian.h"

Vec3 Lambertian::randomOnUnitSphere() const
{
	Vec3 v;
	float vSquaredMag;
	float minimumMag = 0.0001f;
	do
	{
		// get vector with each element between -1 and 1
		v = RNG::randomVector({ -1,1 });
		vSquaredMag = v.squaredMagnitude();
	} while (vSquaredMag > 1 || vSquaredMag < minimumMag);
	//repeat until we get something inside the unit sphere but not too small

	return v.normalized();
}

bool Lambertian::scatter(const Ray& rayIn, const HitRecord& rec,
	Vec3& out_attenuation, Ray& out_scattered) const
{
	Vec3 scatterDirection = rec.surfaceNormal + randomOnUnitSphere();
	
	// case that randomOnUnitSphere is -rec.surfaceNormal
	if (scatterDirection.nearZero())
		scatterDirection = rec.surfaceNormal;

	out_attenuation = m_albedo; // how much of the color gets reflected

	out_scattered = Ray(rec.hitPoint, scatterDirection);
	return true;
}