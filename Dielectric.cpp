#include "Dielectric.h"

Vec3 Dielectric::refract(const Vec3& vIn, const Vec3& normal, float refractionIndexRatio) const
{
    Vec3 normalizedVIn = vIn.normalized();
    // angle between the incoming ray and normal 
    float cosTheta = dot(-normalizedVIn, normal);
    // perpendiular (to normal) component
    Vec3 rPerp = refractionIndexRatio * (normalizedVIn + cosTheta * normal);
    // parallel (to normal) component
    Vec3 rPara = -sqrt(fabs(1.0f - rPerp.squaredMagnitude())) * normal;

    return rPerp + rPara;
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

    // EDGE DARKENIG - EXPEIMENTAL
    float hitAngle = dot(-rayIn.direction().normalized(), rec.surfaceNormal);
    if (hitAngle <= 0.4f)
        out_attenuation *=
            std::min(1.0f,
                std::max((hitAngle * 2), 0.5f));

    
    return true;
}


