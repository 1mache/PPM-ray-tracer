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
	
	// (this is actually a cos of angle)
	float scatterAngle = dot(fuzzyDirection, rec.surfaceNormal); // both are normalized

	if(scatterAngle > 0)
		out_scattered = Ray(rec.hitPoint, fuzzyDirection);
	else 
		// in case fuzzy direction points inside the surface
		out_scattered = Ray(rec.hitPoint, perfectDirection);

	out_attenuation = m_albedo;

	if (scatterAngle <= MAX_CLEAR_ANGLE)
		out_attenuation = m_albedo * 
			std::min(1.0f, 
				std::max( (scatterAngle*2), MAX_ALBEDO_DARKENING));

	return true;
}