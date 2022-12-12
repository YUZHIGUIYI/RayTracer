//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/material.h>

namespace OneWeek
{
    class dielectric : public material
    {
    public:
        dielectric(double ri);
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;

    public:
        double ref_idx;
    };
}
