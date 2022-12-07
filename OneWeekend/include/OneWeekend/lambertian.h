//
// Created by ZZK on 2022/12/6.
//
#pragma once

#include <OneWeekend/material.h>

namespace OneWeekend
{
    class lambertian : public material
    {
    public:
        lambertian(const vec3& a);
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;

    public:
        vec3 albedo;
    };
}
