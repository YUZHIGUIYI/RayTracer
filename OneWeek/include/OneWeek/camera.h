//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/ray.h>

namespace OneWeek
{
    class camera
    {
    public:
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist,
                double t0 = 0.0, double t1 = 0.0);

        ray get_ray(double s, double t);    // generate ray between time0 and time1

    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
        double time0, time1;    // shutter open/close times
    };
}
