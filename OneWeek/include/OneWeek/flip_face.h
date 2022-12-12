//
// Created by ZZK on 2022/12/11.
//

#pragma once

#include <OneWeek/hittable.h>

namespace OneWeek
{
    class flip_face : public hittable
    {
    public:
        flip_face(std::shared_ptr<hittable> p);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        std::shared_ptr<hittable> ptr;
    };
}



















