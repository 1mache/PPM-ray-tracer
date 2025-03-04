#pragma once
class Interval
{
	float m_min, m_max;
public:
	Interval(float min, float max) : m_min(min), m_max(max) {}
	
	float max() const { return m_max; }
	float min() const { return m_min; }

	float size() const { return m_max - m_min; }

	bool contains(float x) const { return (m_min <= x) && (x <= m_max); }
	bool surrounds(float x) const { return (m_min < x) && (x < m_max); }
};