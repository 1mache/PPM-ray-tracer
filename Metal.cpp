#include "Metal.h"

bool Metal::scatter(const Ray& rayIn, const HitRecord& rec, Vec3& out_attenuation, Ray& out_scattered) const
{
	// see reflection image in /theory
	Vec3 scatteredDirection = rayIn.direction() - 
							  2.0f * rayIn.direction().projectionOnNormalized(rec.surfaceNormal);
	out_scattered = Ray(rec.hitPoint, scatteredDirection);
	out_attenuation = m_albedo;
	return true;
}