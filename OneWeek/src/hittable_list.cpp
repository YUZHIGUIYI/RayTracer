//
// Created by ZZK on 2022/12/8.
//

#include <OneWeek/hittable_list.h>
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
        auto checker = std::make_shared<checker_texture>(
                std::make_shared<constant_texture>(vec3(0.2, 0.3, 0.1)),
                std::make_shared<constant_texture>(vec3(0.9, 0.9, 0.9)));

        add(std::make_shared<sphere>(vec3(0.0, -1000.0, 0.0), 1000.0, std::make_shared<lambertian>(checker)));

        int i = 1;
        for (int a = -10; a < 10; ++a)
        {
            for (int b = -10; b < 10; ++b)
            {
                auto choose_mat = random_double();
                vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
                if ((center - vec3(4.0, 0.2, 0.0)).length() > 0.9)
                {
                    if (choose_mat < 0.8) {
                        // diffuse
                        auto albedo = vec3::random() * vec3::random();
                        add(std::make_shared<moving_sphere>(center, center + vec3(0.0, random_double(0.0, 0.5), 0.0), 0.0, 1.0, 0.2,
                                                            std::make_shared<lambertian>(std::make_shared<constant_texture>(albedo))));
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

        add(std::make_shared<sphere>(vec3(0.0, 1.0, 0.0), 1.0,
                                        std::make_shared<dielectric>(1.5)));
        add(std::make_shared<sphere>(vec3(-4.0, 1.0, 0.0), 1.0,
                                        std::make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.4, 0.2, 0.1)))));
        add(std::make_shared<sphere>(vec3(4.0, 1.0, 0.0), 1.0,
                                        std::make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0)));
    }

    void hittable_list::two_perlin_spheres()
    {
        auto pertext= std::make_shared<noise_texture>(4.0);
        add(std::make_shared<sphere>(vec3(0.0, -1000.0, 0.0), 1000.0, std::make_shared<lambertian>(pertext)));
        add(std::make_shared<sphere>(vec3(0.0, 2.0, 0.0), 2.0, std::make_shared<lambertian>(pertext)));
    }

    bool hittable_list::bounding_box(double t0, double t1, aabb &output_box) const
    {
        // calculate the bounding box
        if (objects.empty()) return false;

        aabb temp_box;
        bool first_box = true;

        for (const auto& object : objects)
        {
            if (!object->bounding_box(t0, t1, temp_box)) return false;
            output_box = first_box ? temp_box : (aabb::surrounding_box(output_box, temp_box));
            first_box = false;
        }

        return true;
    }

    void hittable_list::earth()
    {
        int nx, ny, nn;
        unsigned char* texture_data = stbi_load("texture/earthmap.jpg", &nx, &ny, &nn, 0);

        auto earth_surface = std::make_shared<lambertian>(
                std::make_shared<image_texture>(texture_data, nx, ny));
        auto globe = std::make_shared<sphere>(vec3(0.0, 0.0, 0.0), 2.0, earth_surface);

        add(globe);
    }

    void hittable_list::simple_light()
    {
        auto pertext = std::make_shared<noise_texture>(4);
        add(std::make_shared<sphere>(vec3(0.0, -1000.0, 0.0), 1000.0, std::make_shared<lambertian>(pertext)));
        add(std::make_shared<sphere>(vec3(0.0, 2.0, 0.0), 2.0, std::make_shared<lambertian>(pertext)));

        auto difflight = std::make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3(4.0, 4.0, 4.0)));
        add(std::make_shared<sphere>(vec3(0.0, 7.0, 0.0), 2.0, difflight));
        add(std::make_shared<xy_rect>(3.0, 5.0, 1.0, 3.0, -2.0, difflight));
    }

    void hittable_list::cornell_box()
    {
        auto red = make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.65, 0.05, 0.05)));
        auto white = make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
        auto green = make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.12, 0.45, 0.15)));
        auto light = make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3(15.0, 15.0, 15.0)));

        using namespace std;
        add(make_shared<flip_face>(make_shared<yz_rect>(0, 555, 0, 555, 555, green)));
        add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
        add(make_shared<xz_rect>(213, 343, 227, 332, 554, light));
        add(make_shared<flip_face>(make_shared<xz_rect>(0, 555, 0, 555, 555, white)));
        add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
        add(make_shared<flip_face>(make_shared<xy_rect>(0, 555, 0, 555, 555, white)));

        shared_ptr<hittable> box1 = make_shared<box>(vec3(0, 0, 0), vec3(165, 330, 165), white);
        box1 = make_shared<rotate_y>(box1,  15);
        box1 = make_shared<translate>(box1, vec3(265,0,295));
        add(box1);

        shared_ptr<hittable> box2 = make_shared<box>(vec3(0,0,0), vec3(165,165,165), white);
        box2 = make_shared<rotate_y>(box2, -18);
        box2 = make_shared<translate>(box2, vec3(130,0,65));
        add(box2);
    }

    void hittable_list::cornell_smoke()
    {
        auto red = make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.65, 0.05, 0.05)));
        auto white = make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
        auto green = make_shared<lambertian>(std::make_shared<constant_texture>(vec3(0.12, 0.45, 0.15)));
        auto light = make_shared<diffuse_light>(std::make_shared<constant_texture>(vec3(7.0, 7.0, 7.0)));

        using namespace std;
        add(make_shared<flip_face>(make_shared<yz_rect>(0, 555, 0, 555, 555, green)));
        add(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
        add(make_shared<xz_rect>(113, 443, 127, 432, 554, light));
        add(make_shared<flip_face>(make_shared<xz_rect>(0, 555, 0, 555, 555, white)));
        add(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
        add(make_shared<flip_face>(make_shared<xy_rect>(0, 555, 0, 555, 555, white)));

        shared_ptr<hittable> box1 = make_shared<box>(vec3(0, 0, 0), vec3(165, 330, 165), white);
        box1 = make_shared<rotate_y>(box1,  15);
        box1 = make_shared<translate>(box1, vec3(265,0,295));

        shared_ptr<hittable> box2 = make_shared<box>(vec3(0,0,0), vec3(165,165,165), white);
        box2 = make_shared<rotate_y>(box2, -18);
        box2 = make_shared<translate>(box2, vec3(130,0,65));

        add(make_shared<constant_medium>(box1, 0.01, make_shared<constant_texture>(vec3(0.0, 0.0, 0.0))));
        add(make_shared<constant_medium>(box2, 0.01, make_shared<constant_texture>(vec3(1.0, 1.0, 1.0))));
    }

    void hittable_list::final_scene()
    {
        using namespace std;

        static std::vector<std::shared_ptr<hittable>> boxes1;

        auto ground = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.48, 0.83, 0.53)));

        // generate random ground floor
        const int boxes_per_side = 20;
        for (int i = 0; i < boxes_per_side; ++i)
        {
            for (int j = 0; j < boxes_per_side; ++j)
            {
                auto w = 100.0;
                auto x0 = -1000.0 + i * w;
                auto z0 = -1000.0 + j * w;
                auto y0 = 0.0;
                auto x1 = x0 + w;
                auto y1 = random_double(1, 101);
                auto z1 = z0 + w;

                boxes1.push_back(make_shared<box>(vec3(x0, y0, z0), vec3(x1, y1, z1), ground));
            }
        }

        // add bvh_node
        add(make_shared<bvh_node>(boxes1, 0, boxes1.size(), 0.0, 1.0));

        // add light
        auto light = make_shared<diffuse_light>(make_shared<constant_texture>(vec3(7.0, 7.0, 7.0)));
        add(make_shared<xz_rect>(123, 423, 147, 412, 554, light));

        // add brown blurry(moving) sphere
        auto center1 = vec3(400, 400, 200);
        auto center2 = center1 + vec3(30, 0, 0);
        auto moving_sphere_material =
                make_shared<lambertian>(make_shared<constant_texture>(vec3(0.7, 0.3, 0.1)));
        add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

        // add glass sphere
        add(make_shared<sphere>(vec3(260, 150, 45), 50, make_shared<dielectric>(1.5)));

        // add silvery sphere
        add(make_shared<sphere>(
                vec3(0, 150, 145), 50, make_shared<metal>(vec3(0.8, 0.8, 0.9), 10.0)
                ));

        // add blue glass sphere
        auto boundary = make_shared<sphere>(vec3(360, 150, 145), 70, make_shared<dielectric>(1.5));
        add(boundary);
        add(make_shared<constant_medium>(
                boundary, 0.2, make_shared<constant_texture>(vec3(0.2, 0.4, 0.9))
                ));

        // add fog
        boundary = make_shared<sphere>(vec3(0.0, 0.0, 0.0), 5000, make_shared<dielectric>(1.5));
        add(make_shared<constant_medium>(
                boundary, 0.0001, make_shared<constant_texture>(vec3(1, 1, 1))
                ));

        // add earth sphere
        int nx, ny, nn;
        auto tex_data = stbi_load("texture/earthmap.jpg", &nx, &ny, &nn, 0);
        auto emat = make_shared<lambertian>(make_shared<image_texture>(tex_data, nx, ny));
        add(make_shared<sphere>(vec3(400, 200, 400), 100, emat));

        // add perlin marbled sphere
        auto pertext = make_shared<noise_texture>(2.0);
        add(make_shared<sphere>(vec3(220, 280, 300), 80, make_shared<lambertian>(pertext)));

        // add cube made of random spheres
        auto white = make_shared<lambertian>(make_shared<constant_texture>(vec3(0.73, 0.73, 0.73)));
        int ns = 1000;
        static std::vector<std::shared_ptr<hittable>> boxes2;
        for (int j = 0; j < ns; ++j)
        {
            boxes2.push_back(make_shared<sphere>(vec3::random(0, 165), 10, white));
        }

        auto translate_rotate_boxes2 = make_shared<translate>(
                make_shared<rotate_y>(
                        make_shared<bvh_node>(boxes2, 0, boxes2.size(), 0.0, 1.0), 15),
                        vec3(-100, 270, 395));
        add(translate_rotate_boxes2);
    }
}
































