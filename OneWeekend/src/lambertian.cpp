//
// Created by ZZK on 2022/12/6.
//
#include <OneWeekend/lambertian.h>

namespace OneWeekend
{
    lambertian::lambertian(const vec3& a) : albedo(a) {}

    bool lambertian::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 scattered_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scattered_direction);
        attenuation = albedo;
        return true;
    }
}