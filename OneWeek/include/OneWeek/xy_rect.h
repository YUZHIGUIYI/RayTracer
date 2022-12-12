//
// Created by ZZK on 2022/12/11.
//

#pragma once

#include <OneWeek/hittable.h>

namespace OneWeek
{
    class xy_rect : public hittable
    {
    public:
        xy_rect() = default;
        xy_rect(double _x0, double _x1, double _y0, double _y1, double _k, std::shared_ptr<material> mat);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        std::shared_ptr<material> mp;
        double x0, x1, y0, y1, k;
    };
}














