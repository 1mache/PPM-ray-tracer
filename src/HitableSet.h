#pragma once
#include "IHitable.h"

class HitableSet: public IHitable
{
	std::vector<IHitable*> m_hitables;

public:
	explicit HitableSet(size_t size = 0) : m_hitables(size) {}
	HitableSet(std::initializer_list<IHitable*> objects): m_hitables(objects) {}
	HitableSet(std::vector<IHitable*>&& objects) : m_hitables(std::move(objects)) {}

	HitableSet(const HitableSet&) = delete;
	HitableSet& operator=(const HitableSet&) = delete;

	~HitableSet() override;
	size_t size() const { return m_hitables.size(); }
	
	bool isHit(const Ray& ray, Interval tInterval, HitRecord& out_record) const override;
};