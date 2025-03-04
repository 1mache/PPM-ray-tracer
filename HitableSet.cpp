#include "HitableSet.h"

HitableSet::~HitableSet()
{
	for (auto* hitable : m_hitables)
		delete hitable;
}

bool HitableSet::isHit(const Ray& ray, float tMin, float tMax, HitRecord& out_record) const
{
	bool hitSomething = false;
	// t of the closest object we hit so far
	float tClosestSoFar = tMax;
	// iterate over our objects and check if we hit any 
	for (auto* hitable : m_hitables)
	{
		if (hitable->isHit(ray, tMin ,tClosestSoFar ,out_record))
		{
			hitSomething = true;
			// we are looking for the closest thing we hit, thats why we
			// update tMax in isHit accordingly so that we only get hits that are closer
			tClosestSoFar = out_record.t;
		}
	}

	return hitSomething;
}
