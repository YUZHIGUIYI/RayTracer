//
// Created by ZZK on 2022/12/8.
//

#include <OneWeek/sphere.h>
#include <OneWeek/aabb.h>
#include <OneWeek/OneWeekUtils.h>

namespace OneWeek
{
    sphere::sphere() {}

    sphere::sphere(vec3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {}

    bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
    {
        vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius * radius;
        auto discriminant = half_b * half_b - a * c;

        if (discriminant > 0)
        {
            auto root = std::sqrt(discriminant);
            auto temp = (-half_b - root) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.at(rec.t);
                vec3 outward_normal = (rec.p - center) / radius;
                rec.set_face_normal(r, outward_normal);
                rec.mat_ptr = mat_ptr;

                get_sphere_uv((rec.p - center) / radius, rec.u, rec.v); // get uv coordinates of sphere
                return true;
            }
            temp = (-half_b + root) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.at(rec.t);
                vec3 outward_normal = (rec.p - center) / radius;
                rec.set_face_normal(r, outward_normal);
                rec.mat_ptr = mat_ptr;

                get_sphere_uv((rec.p - center) / radius, rec.u, rec.v); // get uv coordinates of sphere
                return true;
            }
        }
        return false;
    }

    bool sphere::bounding_box(double t0, double t1, aabb &output_box) const
    {
        // calculate the bounding box that encapsulate the sphere
        output_box = aabb(
                center - vec3(radius, radius, radius),
                center + vec3(radius, radius, radius));
        return true;
    }

    void sphere::get_sphere_uv(const vec3 &p, double &u, double &v) const
    {
        auto phi = std::atan2(p.z(), p.x());
        auto theta = std::asin(p.y());
        u = 1.0 - (phi + pi) / (2.0 * pi);
        v = (theta + pi / 2.0) / pi;
    }
}


































