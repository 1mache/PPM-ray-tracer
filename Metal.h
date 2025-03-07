#pragma once
#include "Material.h"

class Metal : public Material
{
	using RNG = Utils::RNG;

	static constexpr float MAX_CLEAR_ANGLE = 0.4f;
	static constexpr float MIN_ALBEDO_DARKENING = 0.5f;

	Vec3 m_albedo;
	// how fuzzy is the sphere between 0 and 1, 0 is clear
	float m_fuzziness;
	
public:
	Metal(const Vec3& albedo, float fuzziness) : 
		m_albedo(albedo), m_fuzziness(fuzziness <= 1.0f ? fuzziness : 1.0f)
	{};

	virtual bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const override;
};

