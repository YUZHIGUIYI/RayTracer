//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <atomic>
#include <OneWeek/camera.h>
#include <OneWeek/hittable_list.h>

namespace OneWeek
{
    class Renderer
    {
    public:
        Renderer(int width, int height, int samples);
        ~Renderer() = default;

        void set_image_size(int width, int height);
        void set_camera(std::unique_ptr<camera> other_cam);
        void set_scene(std::unique_ptr<hittable_list> other_world);
        void set_scene(std::shared_ptr<hittable> object);

        void run();
        void run_multithreading(int threads = 8);

    private:
        vec3 ray_color(const ray& r, int depth);
        void kernel(int index);

    private:
        int image_width, image_height, image_size;
        int samples_per_pixel;
        int max_depth;
        double aspect_ratio;
        int thread_num;
        int blocks;

        static const vec3 background;

        std::atomic<int64_t> speed_of_progress;

        std::unique_ptr<camera> cam;
        std::unique_ptr<hittable_list> world;

        std::vector<vec3> output_color;
    };
}
