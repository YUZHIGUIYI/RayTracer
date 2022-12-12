//
// Created by ZZK on 2022/12/9.
//

#pragma once

#include <OneWeek/texture.h>
#include <memory>

namespace OneWeek
{
    class checker_texture : public texture
    {
    public:
        checker_texture() = default;
        checker_texture(std::shared_ptr<texture> t0, std::shared_ptr<texture> t1);

        virtual vec3 value(double u, double v, const vec3& p) const override;

    public:
        std::shared_ptr<texture> odd;
        std::shared_ptr<texture> even;
    };
}































