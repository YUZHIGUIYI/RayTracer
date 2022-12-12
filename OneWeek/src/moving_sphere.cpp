//
// Created by ZZK on 2022/12/8.
//

#include <cmath>
#include <OneWeek/moving_sphere.h>
#include <OneWeek/aabb.h>

namespace OneWeek
{
    moving_sphere::moving_sphere() {}

    moving_sphere::moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, std::shared_ptr<material> m)
    : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {}

    bool moving_sphere::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        vec3 oc = r.origin() - center(r.time());
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;

        if (discriminant > 0.0)
        {
            auto root = std::sqrt(discriminant);

            auto temp = (-half_b - root) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.at(rec.t);
                vec3 outward_normal = (rec.p - center(r.time())) / radius;
                rec.set_face_normal(r, outward_normal);
                rec.mat_ptr = mat_ptr;
                return true;
            }

            temp = (-half_b + root) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.at(rec.t);
                vec3 outward_normal = (rec.p - center(r.time())) / radius;
                rec.set_face_normal(r, outward_normal);
                rec.mat_ptr = mat_ptr;
                return true;
            }
        }

        return false;
    }

    vec3 moving_sphere::center(double time) const
    {
        return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
    }

    bool moving_sphere::bounding_box(double t0, double t1, aabb &output_box) const
    {
        // calculate the bounding box that encapsulate the moving sphere
        aabb box0(
                center(t0) - vec3(radius, radius, radius),
                center(t0) + vec3(radius, radius, radius));
        aabb box1(
                center(t1) - vec3(radius, radius, radius),
                center(t1) + vec3(radius, radius, radius));
        // TODO: finish this function
        output_box = aabb::surrounding_box(box0, box1);
        return true;
    }
}























