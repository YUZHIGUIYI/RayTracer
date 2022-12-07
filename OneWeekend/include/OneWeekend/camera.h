//
// Created by ZZK on 2022/12/6.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include <OneWeekend/ray.h>

namespace OneWeekend
{
    class camera
    {
    public:
        camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist);

        ray get_ray(double s, double t);

    public:
        vec3 origin;
        vec3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
    };
}

#endif //RAYTRACER_CAMERA_H
