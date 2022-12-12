//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/hittable.h>

namespace OneWeek
{
    class material
    {
    public:
        virtual vec3 emitted(double u, double v, const vec3& p) const
        {
            return vec3(0.0, 0.0, 0.0);
        }

        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

        virtual ~material() = default;
    };
}
