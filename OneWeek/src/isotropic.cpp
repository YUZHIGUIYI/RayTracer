//
// Created by ZZK on 2022/12/11.
//

#include <OneWeek/isotropic.h>
#include <OneWeek/texture.h>

namespace OneWeek
{

    isotropic::isotropic(std::shared_ptr<texture> a) : albedo(a) {}

    bool isotropic::scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const
    {
        scattered = ray(rec.p, random_unit_sphere(), r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.p);
        return true;
    }
}






















