//
// Created by ZZK on 2022/12/11.
//

#include <OneWeek/box.h>
#include <OneWeek/aabb.h>
#include <OneWeek/xy_rect.h>
#include <OneWeek/yz_rect.h>
#include <OneWeek/xz_rect.h>
#include <OneWeek/flip_face.h>

namespace OneWeek
{

    box::box(const vec3 &p0, const vec3 &p1, std::shared_ptr<material> ptr)
    {
        box_min= p0;
        box_max = p1;

        using namespace std;
        sides.push_back(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
        sides.push_back(make_shared<flip_face>(
                make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr)));

        sides.push_back(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
        sides.push_back(make_shared<flip_face>(
                make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr)));

        sides.push_back(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
        sides.push_back(make_shared<flip_face>(
                make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr)));
    }

    bool box::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        // TODO: Can be more sufficient
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& side : sides)
        {
            if (side->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    bool box::bounding_box(double t0, double t1, aabb &output_box) const
    {
        output_box = aabb(box_min, box_max);
        return true;
    }
}




































