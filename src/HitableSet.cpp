#include "HitableSet.h"

HitableSet::~HitableSet()
{
	for (auto* hitable : m_hitables)
		delete hitable;
}

bool HitableSet::isHit(const Ray& ray, Interval tInterval, HitRecord& out_record) const
{
	bool hitSomething = false;
	// t of the closest object we hit so far
	float tClosestSoFar = tInterval.max();
	// iterate over our objects and check if we hit any 
	for (auto* hitable : m_hitables)
	{
		if(!hitable)
		{
			//should never happen
			std::clog << "Null hitable!" << std::endl;
		}
		else if (hitable->isHit(ray, {tInterval.min(), tClosestSoFar}, out_record))
		{
			hitSomething = true;
			// we are looking for the closest thing we hit, thats why we
			// update tMax in isHit accordingly so that we only get hits that are closer
			tClosestSoFar = out_record.t;
		}
	}

	return hitSomething;
}
