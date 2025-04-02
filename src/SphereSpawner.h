#pragma once
#include <memory>
#include <random>
#include <functional>
#include "ppmRT.h"
#include "Materials.h"
#include "Sphere.h"

class SphereSpawner
{
	using rng = Utils::RNG;

	// For metal fuzziness:
	// we want something that has a low success rate for the fuzziness of metal
	static constexpr short BINOMIAL_TRIES = 30;
	static constexpr float BINOMIAL_PR_SUCCESS = 0.1f;

	// our generator
	std::random_device m_rd;
	std::mt19937 m_generator = std::mt19937(m_rd());

	std::binomial_distribution<int> m_fuzzBinomialDist{ BINOMIAL_TRIES, BINOMIAL_PR_SUCCESS };

	// distribution 0 - 2 because we have 3 materials => this is the range
	// this way we get mostly matte spheres, then a little more metal and then sometimes glass
	std::binomial_distribution<int> m_intBinomial{ 2, 0.5 };

	// generates a random material (both in kind and in properties)
	std::shared_ptr<Material> randomMaterial();
public:
	SphereSpawner() = default;
	SphereSpawner(SphereSpawner&) = delete;
	SphereSpawner& operator=(SphereSpawner&) = delete;

	Sphere* spawnRandomSphere(Interval posInterval, Interval radiusInterval);
};

