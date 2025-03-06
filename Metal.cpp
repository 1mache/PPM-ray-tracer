#include "Metal.h"

bool Metal::scatter(const Ray& rayIn, const HitRecord& rec, Vec3& out_attenuation, Ray& out_scattered) const
{
	// perfect reflection
	// (see reflection image in /theory)
	Vec3 perfectDirection = (rayIn.direction() -
							   2.0f * rayIn.direction().projectionOnNormalized(rec.surfaceNormal));
	
	// add fuzziness
	// and normalize it so fuzziness doesnt affect length
	Vec3 fuzzyDirection = (perfectDirection +  m_fuzziness * RNG::randomOnUnitSphere()).normalized();
	
	if(dot(fuzzyDirection, rec.surfaceNormal) > 0)
		out_scattered = Ray(rec.hitPoint, fuzzyDirection);
	else 
		// in case fuzzy direction points inside the surface
		out_scattered = Ray(rec.hitPoint, perfectDirection);

	out_attenuation = m_albedo;
	return true;
}