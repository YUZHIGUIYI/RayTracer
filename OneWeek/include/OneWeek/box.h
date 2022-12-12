//
// Created by ZZK on 2022/12/11.
//

#pragma once

#include <OneWeek/hittable.h>
#include <vector>

namespace OneWeek
{
    class box : public hittable
    {
    public:
        box() = default;
        box(const vec3& p0, const vec3& p1, std::shared_ptr<material> ptr);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

    public:
        vec3 box_min;
        vec3 box_max;
        std::vector<std::shared_ptr<hittable>> sides;
    };
}


















