//
// Created by ZZK on 2022/12/11.
//

#pragma once

#include <OneWeek/hittable.h>

namespace OneWeek
{
    class texture;

    class constant_medium : public hittable
    {
    public:
        constant_medium(std::shared_ptr<hittable> b, double d, std::shared_ptr<texture> a);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        std::shared_ptr<hittable> boundary;
        std::shared_ptr<material> phase_function;
        double neg_inv_density;
    };
}




































