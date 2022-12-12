//
// Created by ZZK on 2022/12/11.
//
#pragma once

#include <OneWeek/hittable.h>

namespace OneWeek
{
    class xz_rect : public hittable
    {
    public:
        xz_rect() = default;
        xz_rect(double  _x0, double _x1, double _z0, double _z1, double _k, std::shared_ptr<material> mat);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        std::shared_ptr<material> mp;
        double x0, x1, z0, z1, k;
    };
}
