#pragma once
#include <random>
#include "Vec3.h"
#include "Interval.h"

namespace Utils 
{
    class RNG
    {
        inline static std::random_device m_rd; // get a random seed from the OS
        // initialize PRNG with the seed
        inline static std::mt19937 m_generator = std::mt19937(m_rd());
        // initialize distribution
        inline static std::uniform_real_distribution<float> m_distribution01{ 0.0f, 1.0f };

    public:
        RNG() = delete;
        RNG& operator=(const RNG&) = delete;

        inline static float random0to1()
        {
            return m_distribution01(m_generator);
        }

        inline static float randomInRange(const Interval& range)
        {
            return random0to1() * range.size() + range.min();
        }

        static Vec3 randomVector(const Interval& elementInterval);

        //generates a random vector inside the unit sphere
        static Vec3 randomOnUnitSphere();
    };
}