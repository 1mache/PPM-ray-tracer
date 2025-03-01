#include "Sphere.h"

bool Sphere::isHit(const Ray& ray, HitRecord& record)
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
		// find t
		float t1 = (-b + sqrt(discriminant)) / (2 * a);
		float t2 = (-b - sqrt(discriminant)) / (2 * a);
		float t = std::min(t1, t2);
		// populate hit record
		record.t = t;
		record.hitPoint = ray.pointByParam(t);
		record.surfaceNormal = (record.hitPoint - m_center).normalized();
	}

	return discriminant > 0;
}
