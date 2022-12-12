//
// Created by ZZK on 2022/12/9.
//

#include <iostream>
#include <algorithm>
#include <OneWeek/bvh_node.h>
#include <OneWeek/hittable_list.h>
#include <OneWeek/OneWeekUtils.h>

namespace OneWeek
{
    bvh_node::bvh_node(hittable_list &list, double time0, double time1)
    : bvh_node(list.objects, 0, list.objects.size(), time0, time1) {}

    bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>> &objects, size_t start, size_t end, double time0, double time1)
    {
        /*
         * 1. randomly select an axis to segment
         * 2. use "sort()" function to sort entities
         * 3. half split, half objects for each subtree
         */
        // TODO: fix me
        auto src_objects = objects;

        int axis = random_int(0, 2);

        auto comparator = (axis == 0) ? &bvh_node::box_x_compare : (
                axis == 1 ? &bvh_node::box_y_compare : &bvh_node::box_z_compare);

        size_t object_span = end - start;

        if (object_span == 1)
        {
            left = right = src_objects[start];
        } else if (object_span == 2)
        {
            if (comparator(src_objects[start], src_objects[start + 1]))
            {
                left = src_objects[start];
                right = src_objects[start + 1];
            } else
            {
                left = src_objects[start + 1];
                right = src_objects[start];
            }
        } else
        {
            std::sort(src_objects.begin() + start, src_objects.begin() + end, comparator);

            auto mid = start + object_span / 2;
            left = std::make_shared<bvh_node>(src_objects, start, mid, time0, time1);
            right = std::make_shared<bvh_node>(src_objects, mid, end, time0, time1);
        }

        aabb box_left, box_right;
        if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
        {
            std::cerr << "No bounding box in bvh_node constructor.\n";
        }

        box = aabb::surrounding_box(box_left, box_right);
    }

    bool bvh_node::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        if (!box.hit(r, t_min, t_max)) return false;

        bool hit_left = left->hit(r, t_min, t_max, rec);
        bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

        return hit_left || hit_right;
    }

    bool bvh_node::bounding_box(double t0, double t1, aabb &output_box) const
    {
        output_box = box;
        return true;
    }

    bool bvh_node::box_compare(const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b, int axis)
    {
        aabb box_a;
        aabb box_b;

        if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
        {
            std::cerr << "No bounding box in bvh_node constructor.\n";
        }

        return box_a.min().e[axis] < box_b.min().e[axis];
    }

    bool bvh_node::box_x_compare(const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b)
    {
        return box_compare(a, b, 0);
    }

    bool bvh_node::box_y_compare(const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b)
    {
        return box_compare(a, b, 1);
    }

    bool bvh_node::box_z_compare(const std::shared_ptr<hittable> &a, const std::shared_ptr<hittable> &b)
    {
        return box_compare(a, b, 2);
    }
}






























