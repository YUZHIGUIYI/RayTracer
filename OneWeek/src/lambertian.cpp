//
// Created by ZZK on 2022/12/8.
//

#include <OneWeek/lambertian.h>
#include <OneWeek/texture.h>

namespace OneWeek
{
    lambertian::lambertian(std::shared_ptr<texture> a) : albedo(a) {}

    bool lambertian::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 scattered_direction = rec.normal + random_unit_vector();
        scattered = ray(rec.p, scattered_direction, r_in.time());    // be sure the scattered light and incident light exist at the same time point
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }
}