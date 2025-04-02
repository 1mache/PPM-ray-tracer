#include "SphereSpawner.h"


std::shared_ptr<Material> SphereSpawner::randomMaterial()
{
    using materialPtr = std::shared_ptr<Material>;

    // vector of material constructing functions
    std::vector<std::function<materialPtr()>> materialConstructors =
    {
        // had to cast them explicitly on return
        []() -> materialPtr
            { return std::static_pointer_cast<Material>(
                std::make_shared<Lambertian>(rng::randomVector(Interval(0.0f, 1.0f)))); },

        [this]() -> materialPtr
            { float fuzziness = (float)m_fuzzBinomialDist(m_generator) / BINOMIAL_PR_SUCCESS;
              return std::static_pointer_cast<Material>(      // value between 0 and 1
                std::make_shared<Metal>( rng::randomVector(Interval(0.0f, 1.0f)), fuzziness)); },

        []() -> materialPtr // I chose to not randomize here
            { return std::static_pointer_cast<Material>(std::make_shared<Dielectric>(Constants::GLASS_REFRACTION)); }
    };

    uint8_t randomId = m_intBinomial(m_generator);
    return materialConstructors[randomId]();
}

Sphere* SphereSpawner::spawnRandomSphere(Interval posInterval, Interval radiusInterval)
{
    float radius = rng::randomInRange(radiusInterval);
    Vec3 position = { rng::randomInRange(posInterval), radius - 0.5f , rng::randomInRange(posInterval) };

    // could use smart pointers but then id have to transfer ownership and it would be a little inconsistent
    // with how HittableSet stores them raw
    return new Sphere(position, radius, randomMaterial());
}