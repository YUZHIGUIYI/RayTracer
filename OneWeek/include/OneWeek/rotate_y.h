//
// Created by ZZK on 2022/12/11.
//

#pragma once

#include <OneWeek/hittable.h>
#include <OneWeek/aabb.h>

namespace OneWeek
{
    class rotate_y : public hittable
    {
    public:
        rotate_y(std::shared_ptr<hittable> p, double angle);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        std::shared_ptr<hittable> ptr;
        double sin_theta;
        double cos_theta;
        bool hasbox;
        aabb bbox;
    };
}



























