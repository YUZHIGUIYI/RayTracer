//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/checker_texture.h>
#include <cmath>

namespace OneWeek
{

    checker_texture::checker_texture(std::shared_ptr<texture> t0, std::shared_ptr<texture> t1)
    : odd(t0), even(t1) {}

    vec3 checker_texture::value(double u, double v, const vec3 &p) const
    {
        auto sines = std::sin(10 * p.x()) * std::sin(10 * p.y()) * std::sin(10 * p.z());
        if (sines < 0.0)
            return odd->value(u, v, p);
        else
            return even->value(u, v, p);
    }
}












