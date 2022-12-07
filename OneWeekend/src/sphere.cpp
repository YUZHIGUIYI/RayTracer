//
// Created by ZZK on 2022/12/6.
//

#include <OneWeekend/sphere.h>
#include <cmath>

namespace OneWeekend
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
                return true;
            }
        }
        return false;
    }
}