//
// Created by ZZK on 2022/12/6.
//

#include <OneWeekend/hittable_list.h>
#include <OneWeekend/sphere.h>
#include <OneWeekend/metal.h>
#include <OneWeekend/lambertian.h>
#include <OneWeekend/dielectric.h>
#include <OneWeekend/OneWeekendUtils.h>

namespace OneWeekend
{
    hittable_list::hittable_list() {}

    hittable_list::hittable_list(std::shared_ptr<hittable> object)
    {
        add(object);
    }

    void hittable_list::clear()
    {
        objects.clear();
    }

    void hittable_list::add(std::shared_ptr<hittable> object)
    {
        objects.push_back(object);
    }

    bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object : objects)
        {
            if (object->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    void hittable_list::random_scene()
    {
        add(std::make_shared<sphere>(vec3(0.0, -1000.0, 0.0), 1000.0, std::make_shared<lambertian>(vec3(0.5, 0.5, 0.5))));

        for (int a = -11; a < 11; ++a)
        {
            for (int b = -11; b < 11; ++b)
            {
                auto choose_mat = random_double();
                vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
                if ((center - vec3(4.0, 0.2, 0.0)).length() > 0.9)
                {
                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = vec3::random() * vec3::random();
                        add(std::make_shared<sphere>(center, 0.2, std::make_shared<lambertian>(albedo)));
                    } else if (choose_mat < 0.95) {
                        // metal
                        auto albedo = vec3::random(0.5, 1.0);
                        auto fuzz = random_double(0.0, 0.5);
                        add(std::make_shared<sphere>(center, 0.2, std::make_shared<metal>(albedo, fuzz)));
                    } else {
                        // glass
                        add(std::make_shared<sphere>(center, 0.2, std::make_shared<dielectric>(1.5)));
                    }
                }
            }
        }

        add(std::make_shared<sphere>(vec3(0.0, 1.0, 0.0), 1.0, std::make_shared<dielectric>(1.5)));
        add(std::make_shared<sphere>(vec3(-4.0, 1.0, 0.0), 1.0, std::make_shared<lambertian>(vec3(0.4, 0.2, 0.1))));
        add(std::make_shared<sphere>(vec3(4.0, 1.0, 0.0), 1.0, std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));
    }
}

































