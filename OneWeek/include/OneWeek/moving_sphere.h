//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/hittable.h>
#include <memory>

namespace OneWeek
{
    class moving_sphere : public hittable
    {
    public:
        moving_sphere();
        moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, std::shared_ptr<material> m);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;
        vec3 center(double time) const;

    public:
        vec3 center0, center1;
        double time0, time1;
        double radius;
        std::shared_ptr<material> mat_ptr;
    };
}































