//
// Created by ZZK on 2022/12/10.
//

#pragma once

#include <OneWeek/material.h>

namespace OneWeek
{
    class texture;

    class diffuse_light : public material
    {
    public:
        diffuse_light(std::shared_ptr<texture> a);

        virtual vec3 emitted(double u, double v, const vec3& p) const override;
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;

    public:
        std::shared_ptr<texture> emit;
    };
}
