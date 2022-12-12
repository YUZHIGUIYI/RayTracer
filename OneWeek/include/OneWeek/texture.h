//
// Created by ZZK on 2022/12/9.
//

#pragma once

#include <OneWeek/vec3.h>

namespace OneWeek
{
    class texture
    {
    public:
        virtual vec3 value(double u, double v, const vec3& p) const = 0;
        ~texture() = default;
    };
}