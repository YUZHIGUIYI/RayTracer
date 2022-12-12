//
// Created by ZZK on 2022/12/9.
//

#pragma once

#include <OneWeek/texture.h>

namespace OneWeek
{
    class constant_texture : public texture
    {
    public:
        constant_texture() = default;
        constant_texture(vec3 c);

        virtual vec3 value(double u, double v, const vec3& p) const override;

    public:
        vec3 color;
    };
}
