//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/texture.h>

namespace OneWeek
{
    class image_texture : public texture
    {
    public:
        image_texture() = default;
        image_texture(unsigned char* pixels, int A, int B);

        ~image_texture();

        virtual vec3 value(double u, double v, const vec3& p) const override;

    public:
        unsigned char* data;
        int nx, ny;
    };
}
