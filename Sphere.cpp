#include "Sphere.h"

bool Sphere::isHit(const Ray& ray, float tMin, float tMax, HitRecord& out_record) const
{
	// The components of the quadratic equation are derived from 
	// dot(p-c, p-c) = r^2 where p is a point on a ray ,c is the center of the sphere
	// and r is the radius of the sphere.
	// We ask is there a param t in ray equation that satisfies that.

	Vec3 oc = ray.origin() - m_center;
	float a = dot(ray.normalizedDirection(), ray.normalizedDirection());
	float b = 2.0f * dot(oc, ray.normalizedDirection());
	float c = dot(oc, oc) - m_radius * m_radius;

	float discriminant = b * b - 4 * a * c; // good ol` discriminant

	if (discriminant > 0)
	{
		// two solutions of the quadr. equation
		float t1 = (-b - sqrt(discriminant)) / (2 * a); 
		float t2 = (-b + sqrt(discriminant)) / (2 * a); 
		float t; // final t
		bool tFound = false; // did we find a "good" t 
		if (tMin <= t1 && t1 <= tMax) // is t1 in bounds
		{
			t = t1;
			tFound = true;
		}
		if (tMin <= t2 && t2 <= tMax) // is t2 in bounds
		{
			// if we already have a t, pick the smaller out of the 2
			if (tFound) t = std::min(t, t2);
			else t = t2; // otherwise just pick t2
			tFound = true;
		}

		// if t was found populate hit record
		if(tFound)
		{
			out_record.t = t;
			out_record.hitPoint = ray.pointByParam(t);
			out_record.surfaceNormal = (out_record.hitPoint - m_center).normalized();
			return true;
		}
	}

	return false;
}
