#pragma once
#include "IHitable.h"

class Material
{
public:
	virtual ~Material() = default;
	virtual bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const = 0;
};

// =========Matte objects===========
class Lambertian : public Material
{
	using RNG = Utils::RNG;

	// how much of every color gets reflected
	Vec3 m_albedo;
public:
	Lambertian(const Vec3& albedo) : m_albedo(albedo) {}

	virtual bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const override;
};

// =========Reflective objects===========
class Metal : public Material
{
	using RNG = Utils::RNG;

	static constexpr float MAX_CLEAR_ANGLE = 0.4f;
	static constexpr float MAX_ALBEDO_DARKENING = 0.5f;

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

// =========Refractive objects===========
class Dielectric : public Material
{
	float m_refractionIndex;

	Vec3 refract(const Vec3& vIn, const Vec3& normal, float refractionIndexRatio) const;
	bool shouldReflect(float cosTheta, float refractionIndex) const;
public:
	Dielectric(float refractionIndex) : m_refractionIndex(refractionIndex)
	{}

	bool scatter(
		const Ray& rayIn, // incoming ray
		const HitRecord& rec, // hit record
		Vec3& out_attenuation, // output color attenuation
		Ray& out_scattered // scattered ray
	) const override;
};