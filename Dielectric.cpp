#include "Dielectric.h"

Vec3 Dielectric::refract(const Vec3& vIn, const Vec3& normal, float refractionIndexRatio) const
{
    Vec3 normalizedVIn = vIn.normalized();
    // angle between the incoming ray and normal 
    float cosTheta = dot(-normalizedVIn, normal);
    float sinTheta = sqrtf(1.0f - cosTheta * cosTheta);

    Vec3 direction;
    // sin of refracted angle = rIR * sinTheta, (snelle`s law)
    // sin cannot be greater than 1. => sometimes refraction is impossible
    bool cannotRefract = refractionIndexRatio* sinTheta > 1.0f;
    if (cannotRefract || shouldReflect(cosTheta, refractionIndexRatio))
        //Cant refract, need to reflect instead
        direction = (vIn -
            2.0f * vIn.projectionOnNormalized(normal));
    else
    {
        // perpendiular (to normal) component
        Vec3 rPerp = refractionIndexRatio * (normalizedVIn + cosTheta * normal);
        // parallel (to normal) component
        Vec3 rPara = -sqrtf(fabs(1.0f - rPerp.squaredMagnitude())) * normal;
        direction = rPerp + rPara;
    }

    return direction;
}

bool Dielectric::shouldReflect(float cosTheta, float refractionIndex) const
{
    // using https://en.wikipedia.org/wiki/Schlick%27s_approximation calculate the
    // "probability" of light being reflected 
    float r0 = (1.0f - refractionIndex) / (1.0f + refractionIndex);
    r0 *= r0; // squared

    float coefficient = r0 + (1 - r0) * std::pow((1 - cosTheta), 5);
    // randomly decide by the "probability"
    return coefficient > Utils::RNG::random0to1();
}

bool Dielectric::scatter(const Ray& rayIn, const HitRecord& rec, Vec3& out_attenuation, Ray& out_scattered) const
{
    out_attenuation = Vec3(1.0f, 1.0f, 1.0f); // refraction doesnt influence color
    
    float refractionIndexRatio;
    if (rec.frontFace)//from air to material
        refractionIndexRatio = 1.0f / m_refractionIndex;
    else // from material to air
        refractionIndexRatio = m_refractionIndex;

    Vec3 refractedDirection = refract(rayIn.direction(), rec.surfaceNormal, refractionIndexRatio);
    out_scattered = Ray(rec.hitPoint, refractedDirection);
    
    return true;
}


