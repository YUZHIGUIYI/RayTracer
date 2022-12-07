//
// Created by ZZK on 2022/12/6.
//

#pragma once

#include <OneWeekend/hittable.h>
#include <memory>
#include <vector>

namespace OneWeekend
{
    class hittable_list : public hittable
    {
    public:
        hittable_list();
        hittable_list(std::shared_ptr<hittable> object);

        void clear();
        void add(std::shared_ptr<hittable> object);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

        // A example to include spheres
        void random_scene();

    public:
        std::vector<std::shared_ptr<hittable>> objects;
    };
}





































