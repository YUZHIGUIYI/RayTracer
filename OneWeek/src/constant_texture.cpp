//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/constant_texture.h>

namespace OneWeek
{
    constant_texture::constant_texture(OneWeek::vec3 c) : color(c) {}

    vec3 constant_texture::value(double u, double v, const OneWeek::vec3 &p) const
    {
        return color;
    }
}