//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/material.h>

namespace OneWeek
{
    class metal : public material
    {
    public:
        metal(const vec3& a, double f);
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;

    public:
        vec3 albedo;
        double fuzziness;
    };
}
