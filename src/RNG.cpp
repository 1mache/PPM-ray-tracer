#include "RNG.h"
namespace Utils
{
    Vec3 RNG::randomVector(const Interval& elementInterval)
    {
        Vec3 result = { random0to1(), random0to1(), random0to1() };
        // get result in the range of the given interval
        result *= elementInterval.size();
        result += Vec3(elementInterval.min(), elementInterval.min(), elementInterval.min());
        return result;
    };

    Vec3 RNG::randomOnUnitSphere()
    {
        Vec3 v;
        float vSquaredMag;
        float minimumMag = 0.0001f;
        do
        {
            // get vector with each element between -1 and 1
            v = randomVector({ -1,1 });
            vSquaredMag = v.squaredMagnitude();
        } while (vSquaredMag > 1 || vSquaredMag < minimumMag);
        //repeat until we get something inside the unit sphere but not too small

        return v.normalized();
    }
    std::shared_ptr<Material> RNG::randomMaterial()
    {
        using materialPtr = std::shared_ptr<Material>;
        // we want something that has a low success rate for the fuzziness of metal
        const uint8_t binomialTries = 30;
        const float   binomialPrSuccess = 0.1f;

        // distribution 0 - 2 because we have 3 materials => this is the range of id`s
        auto intUniformDist = std::uniform_int_distribution(0, 2);

        // vector of material constructing functions
        std::vector<std::function<materialPtr()>> materialConstructors =
        {
            // had to cast them explicitly
            []() -> materialPtr
                { return std::static_pointer_cast<Material>(
                    std::make_shared<Lambertian>(randomVector(Interval(0.0f, 1.0f)))); },
            [=]() -> materialPtr
                { auto fuzzBinomialDist = std::binomial_distribution(binomialTries, binomialPrSuccess);
                  return std::static_pointer_cast<Material>(      // value between 0 and 1
                    std::make_shared<Metal>(Interval(0.0f, 1.0f), fuzzBinomialDist(m_generator) / binomialTries)); },
            []() -> materialPtr // I chose to not randomize here
                { return std::static_pointer_cast<Material>(std::make_shared<Dielectric>(Constants::GLASS_REFRACTION));}
        };

        uint8_t randomId = intUniformDist(m_generator);
        return materialConstructors[randomId]();
    }
}