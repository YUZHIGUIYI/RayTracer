//
// Created by ZZK on 2022/12/9.
//

#pragma once

#include <OneWeek/ray.h>

namespace OneWeek
{
    class aabb
    {
    public:
        aabb() = default;
        aabb(const vec3& a, const vec3& b);

        vec3 min() const;
        vec3 max() const;

        bool hit(const ray& r, double tmin, double tmax) const;

        static aabb surrounding_box(const aabb& box0, const aabb& box1);

    public:
        vec3 _min;
        vec3 _max;
    };
}