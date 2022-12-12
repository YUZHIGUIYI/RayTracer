//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/image_texture.h>

namespace OneWeek
{
    image_texture::image_texture(unsigned char *pixels, int A, int B)
    : data(pixels), nx(A), ny(B) {}

    image_texture::~image_texture()
    {
        delete data;
    }

    vec3 image_texture::value(double u, double v, const vec3 &p) const
    {
        // if we have no texture data, then always emit cyan (as a debugging aid)
        if (data == nullptr) return vec3(0.0, 1.0, 1.0);

        auto i = static_cast<int>(u * nx);
        auto j =static_cast<int>((1- v) * ny - 0.001);

        if (i < 0) i = 0;
        if (j < 0) j = 0;
        if (i > nx - 1) i = nx - 1;
        if (j > ny - 1) j = ny - 1;

        auto r = static_cast<int>(data[3 * i + 3 * nx * j + 0]) / 255.0;
        auto g = static_cast<int>(data[3 * i + 3 * nx * j + 1]) / 255.0;
        auto b = static_cast<int>(data[3 * i + 3 * nx * j + 2]) / 255.0;

        return vec3(r, g, b);
    }
}

























