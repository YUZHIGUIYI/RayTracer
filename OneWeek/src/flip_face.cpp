//
// Created by ZZK on 2022/12/11.
//

#include <OneWeek/flip_face.h>

namespace OneWeek
{

    flip_face::flip_face(std::shared_ptr<hittable> p) : ptr(p) {}

    bool flip_face::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        if (!ptr->hit(r, t_min, t_max, rec))
            return false;

        rec.front_face = !rec.front_face;
        return true;
    }

    bool flip_face::bounding_box(double t0, double t1, aabb &output_box) const
    {
        return ptr->bounding_box(t0, t1, output_box);
    }
}

























