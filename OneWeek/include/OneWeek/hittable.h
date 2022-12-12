//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <memory>
#include <OneWeek/ray.h>

namespace OneWeek
{
    class material;

    class aabb;

    struct hit_record
    {
        vec3 p;
        vec3 normal;
        std::shared_ptr<material> mat_ptr;
        double t;
        // store uv info
        double u;
        double v;
        bool front_face;

        inline void set_face_normal(const ray& r, const vec3& outward_normal)
        {
            front_face = dot(r.direction(), outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };

    class hittable
    {
    public:
        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
        // a function to calculate the bounding box that encapsulate the hittable class
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const = 0;
    };
}





























