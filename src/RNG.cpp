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
}