//
// Created by ZZK on 2022/12/6.
//
#pragma once

#include <OneWeekend/hittable.h>

namespace OneWeekend
{
    class material
    {
    public:
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;

        virtual ~material() = default;
    };
}
