//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/vec3.h>

namespace OneWeek
{
    class ray
    {
    public:
        ray();
        ray(const vec3& origin, const vec3& direction, double time = 0.0);

        vec3 origin() const;
        vec3 direction() const;
        double time() const;
        vec3 at(double t) const;

    public:
        vec3 orig;
        vec3 dir;
        double tm;
    };
}
