//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/material.h>

namespace OneWeek
{
    class texture;

    class lambertian : public material
    {
    public:
        lambertian(std::shared_ptr<texture> a);
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override;

    public:
        std::shared_ptr<texture> albedo;
    };
}
