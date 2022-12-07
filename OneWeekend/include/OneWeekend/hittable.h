//
// Created by ZZK on 2022/12/6.
//

#pragma once

#include <OneWeekend/ray.h>
#include <memory>

namespace OneWeekend
{
    class material;

    struct hit_record
    {
        vec3 p;
        vec3 normal;
        std::shared_ptr<material> mat_ptr;
        double t;
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
    };
}
















