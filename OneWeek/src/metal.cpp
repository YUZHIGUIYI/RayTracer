//
// Created by ZZK on 2022/12/8.
//

#include <OneWeek/metal.h>

namespace OneWeek
{
    metal::metal(const vec3& a, double f) : albedo(a), fuzziness(f < 1.0 ? f : 1.0 ) {}

    bool metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzziness * random_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);  // dot小于0则认为吸收了光线
    }
}