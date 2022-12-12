//
// Created by ZZK on 2022/12/11.
//

#pragma once

#include <OneWeek/hittable.h>

namespace OneWeek
{
    class yz_rect : public hittable
    {
    public:
        yz_rect() = default;
        yz_rect(double  _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<material> mat);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        std::shared_ptr<material> mp;
        double y0, y1, z0, z1, k;
    };
}
