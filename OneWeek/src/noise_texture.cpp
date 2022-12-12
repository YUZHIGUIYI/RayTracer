//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/noise_texture.h>
#include <cmath>

namespace OneWeek
{
    noise_texture::noise_texture(double sc) : scale(sc) {}

    vec3 noise_texture::value(double u, double v, const vec3 &p) const
    {
        //return vec3(1.0, 1.0, 1.0) * 0.5 * (1.0 + noise.noise(scale *  p));
        //return vec3(1.0, 1.0, 1.0) * noise.turb(scale * p);   // net material
        return vec3(1.0, 1.0, 1.0) * 0.5 * (1.0 + std::sin(scale * p.z() + 10 * noise.turb(p)));    // marble material
    }
}