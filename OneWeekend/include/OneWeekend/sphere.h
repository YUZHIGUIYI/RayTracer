//
// Created by ZZK on 2022/12/6.
//

#pragma once

#include <OneWeekend/hittable.h>
#include <memory>

namespace OneWeekend
{
    class sphere : public hittable
    {
    public:
        sphere();
        sphere(vec3 cen, double r, std::shared_ptr<material> m);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        vec3 center;
        double radius;
        std::shared_ptr<material> mat_ptr;
    };
}
