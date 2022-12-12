
//
// Created by ZZK on 2022/12/11.
//

#include <OneWeek/yz_rect.h>
#include <OneWeek/aabb.h>

namespace OneWeek
{

    yz_rect::yz_rect(double _y0, double _y1, double _z0, double _z1, double _k, std::shared_ptr<material> mat)
    : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {}

    bool yz_rect::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        auto t = (k - r.origin().x()) / r.direction().x();
        if (t < t_min || t > t_max) return false;
        auto y = r.origin().y() + t * r.direction().y();
        auto z = r.origin().z() + t * r.direction().z();
        if (y < y0 || y > y1 || z < z0 || z > z1) return false;
        rec.u = (y - y0) / (y1 - y0);
        rec.v = (z - z0) / (z1 - z0);
        rec.t = t;
        vec3 outward_normal = vec3(1.0, 0.0, 0.0);
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mp;
        rec.p = r.at(t);
        return true;
    }

    bool yz_rect::bounding_box(double t0, double t1, aabb &output_box) const
    {
        output_box = aabb(vec3(k - 0.0001, y0, z0), vec3(k + 0.0001, y1, z1));
        return true;
    }
}



































