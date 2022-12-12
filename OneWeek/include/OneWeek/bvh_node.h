//
// Created by ZZK on 2022/12/9.
//

#pragma once

#include <OneWeek/hittable.h>
#include <OneWeek/aabb.h>
#include <vector>

namespace OneWeek
{
    class hittable_list;

    class bvh_node : public hittable
    {
    public:
        bvh_node() = default;
        bvh_node(hittable_list& list, double time0, double time1);
        bvh_node(std::vector<std::shared_ptr<hittable>>& objects, size_t start, size_t end, double time0, double time1);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

        static bool box_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b, int axis);
        static bool box_x_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b);
        static bool box_y_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b);
        static bool box_z_compare(const std::shared_ptr<hittable>& a, const std::shared_ptr<hittable>& b);

    public:
        std::shared_ptr<hittable> left;
        std::shared_ptr<hittable> right;
        aabb box;
    };
}




























