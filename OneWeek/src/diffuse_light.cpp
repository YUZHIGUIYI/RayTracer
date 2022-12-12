//
// Created by ZZK on 2022/12/10.
//

#include <OneWeek/diffuse_light.h>
#include <OneWeek/texture.h>

namespace OneWeek
{

    diffuse_light::diffuse_light(std::shared_ptr<texture> a)
    : emit(a) {}

    vec3 diffuse_light::emitted(double u, double v, const vec3 &p) const
    {
        return emit->value(u, v, p);
    }

    bool diffuse_light::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        return false;
    }
}