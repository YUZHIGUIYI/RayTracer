//
// Created by ZZK on 2022/12/12.
//

#pragma once

#include <OneWeek/hittable_list.h>

namespace OneWeek
{
    class hittable_world : public hittable_list
    {
    public:
        hittable_world() = default;
        hittable_world(std::shared_ptr<hittable_list> object_list);

        ~hittable_world() = default;

        void clear();
        void add(std::shared_ptr<hittable_list> object_list);

        bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        bool bounding_box(double t0, double t1, aabb& output_box) const override;

        // an example to test all new features in a scene
        void final_scene();

    public:
        std::vector<std::shared_ptr<hittable_list>> scene;
    };
}
