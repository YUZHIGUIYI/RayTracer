//
// Created by ZZK on 2022/12/5.
//
#pragma once

#include <OneWeekend/vec3.h>

namespace OneWeekend
{
    class ray
    {
    public:
        ray() = default;
        ray(const vec3& origin, const vec3& direction);
        vec3 origin() const;
        vec3 direction() const;
        vec3 at(double t) const;

    public:
        vec3 orig;
        vec3 dir;
    };
}
