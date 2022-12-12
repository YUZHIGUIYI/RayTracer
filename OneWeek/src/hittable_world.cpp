//
// Created by ZZK on 2022/12/12.
//

#include <OneWeek/hittable_world.h>
#include <OneWeek/moving_sphere.h>
#include <OneWeek/sphere.h>
#include <OneWeek/constant_medium.h>
#include <OneWeek/xy_rect.h>
#include <OneWeek/yz_rect.h>
#include <OneWeek/xz_rect.h>
#include <OneWeek/flip_face.h>
#include <OneWeek/translate.h>
#include <OneWeek/rotate_y.h>
#include <OneWeek/box.h>
#include <OneWeek/aabb.h>
#include <OneWeek/bvh_node.h>
#include <OneWeek/constant_texture.h>
#include <OneWeek/checker_texture.h>
#include <OneWeek/noise_texture.h>
#include <OneWeek/image_texture.h>
#include <OneWeek/metal.h>
#include <OneWeek/lambertian.h>
#include <OneWeek/dielectric.h>
#include <OneWeek/diffuse_light.h>
#include <OneWeek/OneWeekUtils.h>
#include <OneWeek/stb_image.h>

namespace OneWeek
{

    hittable_world::hittable_world(std::shared_ptr<hittable_list> object_list)
    {
        add(object_list);
    }

    void hittable_world::clear()
    {
        hittable_list::clear();
    }

    void hittable_world::add(std::shared_ptr<hittable_list> object_list)
    {
        scene.push_back(object_list);
    }

    bool hittable_world::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = t_max;

        for (const auto& object_list : scene)
        {
            if (object_list->hit(r, t_min, closest_so_far, temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

    bool hittable_world::bounding_box(double t0, double t1, aabb &output_box) const
    {
        // calculate the bounding box
        if (scene.empty()) return false;

        aabb temp_box;
        bool first_box = true;

        for (const auto& object_list : scene)
        {
            if (!object_list->bounding_box(t0, t1, temp_box)) return false;
            output_box = first_box ? temp_box : (aabb::surrounding_box(output_box, temp_box));
            first_box = false;
        }

        return true;
    }

    void hittable_world::final_scene()
    {
        using namespace std;
        hittable_list boxes1;
        auto ground = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.48, 0.83, 0.53)));

        const int boxes_per_side = 20;
        for (int i = 0; i < boxes_per_side; ++i)
        {
            for (int j = 0; j < boxes_per_side; ++j)
            {
                auto w = 100.0;
                auto x0 = -1000.0 + j * w;
                auto z0 = -1000.0 + j * w;
                auto y0 = 0.0;
                auto x1 = x0 + w;
                auto y1 = random_double(1, 101);
                auto z1 = z0 + w;

                boxes1.add(make_shared<box>(vec3(x0, y0, z0), vec3(x1, y1, z1), ground));
            }
        }

        // hittable_list
        std:;shared_ptr<hittable_list> object_list = std::make_shared<hittable_list>();

        // add bvh_node
        auto node1 = make_shared<bvh_node>(boxes1, 0, 1);
        object_list->add(node1);

        auto light = make_shared<diffuse_light>(make_shared<constant_texture>(vec3(7, 7, 7)));
        object_list->add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

        auto center1 = vec3(400, 400, 200);
        auto center2 = center1 + vec3(30,0,0);
        auto moving_sphere_material =
                make_shared<lambertian>(make_shared<constant_texture>(vec3(0.7, 0.3, 0.1)));
        object_list->add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

        object_list->add(make_shared<sphere>(vec3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
        object_list->add(make_shared<sphere>(
                vec3(0, 150, 145), 50, make_shared<metal>(vec3(0.8, 0.8, 0.9), 10.0)
        ));

        auto boundary = make_shared<sphere>(vec3(360, 150, 145), 70, make_shared<dielectric>(1.5));
        object_list->add(boundary);
        object_list->add(make_shared<constant_medium>(
                boundary, 0.2, make_shared<constant_texture>(vec3(0.2, 0.4, 0.9))
        ));
        boundary = make_shared<sphere>(vec3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
        object_list->add(make_shared<constant_medium>(
                boundary, .0001, make_shared<constant_texture>(vec3(1,1,1))));

        int nx, ny, nn;
        auto tex_data = stbi_load("texture/earthmap.jpg", &nx, &ny, &nn, 0);
        auto emat = make_shared<lambertian>(make_shared<image_texture>(tex_data, nx, ny));
        object_list->add(make_shared<sphere>(vec3(400,200, 400), 100, emat));
        auto pertext = make_shared<noise_texture>(0.1);
        object_list->add(make_shared<sphere>(vec3(220,280, 300), 80, make_shared<lambertian>(pertext)));

        hittable_list boxes2;
        auto white = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
        int ns = 1000;
        for (int j = 0; j < ns; j++) {
            boxes2.add(make_shared<sphere>(vec3::random(0,165), 10, white));
        }

        object_list->add(make_shared<translate>(
                            make_shared<rotate_y>(
                                    make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
                            vec3(-100,270,395)
                    )
        );

        add(object_list);
    }
}


















































