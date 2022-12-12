//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <OneWeek/hittable.h>
#include <memory>

namespace OneWeek
{
    class sphere : public hittable
    {
    public:
        sphere();
        sphere(vec3 cen, double r, std::shared_ptr<material> m);

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
        virtual bool bounding_box(double t0, double t1, aabb& output_box) const override;

        void get_sphere_uv(const vec3& p, double& u, double& v) const;

    public:
        vec3 center;
        double radius;
        std::shared_ptr<material> mat_ptr;
    };
}




























