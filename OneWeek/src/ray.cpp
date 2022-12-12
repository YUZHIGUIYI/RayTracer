//
// Created by ZZK on 2022/12/8.
//

#include <OneWeek/ray.h>

namespace OneWeek
{
    ray::ray() {}

    ray::ray(const vec3& origin, const vec3& direction, double time) : orig(origin), dir(direction), tm(time) {}

    vec3 ray::origin() const
    {
        return orig;
    }

    vec3 ray::direction() const
    {
        return dir;
    }

    double ray::time() const
    {
        return tm;
    }

    vec3 ray::at(double t) const
    {
        return orig + t * dir;
    }
}