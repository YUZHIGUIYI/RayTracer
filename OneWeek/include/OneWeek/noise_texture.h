//
// Created by ZZK on 2022/12/9.
//

#pragma once

#include <OneWeek/texture.h>
#include <OneWeek/perlin.h>

namespace OneWeek
{
    class noise_texture : public texture
    {
    public:
        noise_texture() = default;
        noise_texture(double sc);

        virtual vec3 value(double u, double v, const vec3& p) const override;

    public:
        perlin noise;
        double scale{1.0};
    };
}
