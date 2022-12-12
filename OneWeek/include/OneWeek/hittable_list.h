//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/hittable.h>
#include <vector>

namespace OneWeek
{
    class hittable_list : public hittable
    {
    public:
        hittable_list();
        hittable_list(std::shared_ptr<hittable> object);

        virtual ~hittable_list() = default;

        void clear();
        void add(std::shared_ptr<hittable> object);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

        // an example to include spheres
        void random_scene();
        // an example to include two spheres
        void two_perlin_spheres();
        // an example to include a sphere with earth texture - exclude floor
        void earth();
        // an example to include two spheres and a rectangle light - exclude floor
        void simple_light();
        // an example to include cornell box
        void cornell_box();
        // an example to include cornell box with smoke
        void cornell_smoke();
        // an example to test all new features in a scene
        void final_scene();

    public:
        std::vector<std::shared_ptr<hittable>> objects;
    };
}
















