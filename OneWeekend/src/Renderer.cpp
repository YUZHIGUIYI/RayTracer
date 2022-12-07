//
// Created by ZZK on 2022/12/6.
//

#include <thread>
#include <chrono>
#include <stdexcept>
#include <OneWeekend/Renderer.h>
#include <OneWeekend/material.h>
#include <OneWeekend/thread_stream.h>
#include <OneWeekend/OneWeekendUtils.h>

namespace OneWeekend
{
    Renderer::Renderer(int width, int height, int samples) : image_width(width), image_height(height), samples_per_pixel(samples),
        thread_num(1), image_size(width * height), max_depth(50), aspect_ratio(double(width) / double(height)), speed_of_progress(0)
    {
        vec3 lookfrom(13.0, 2.0, 3.0);
        vec3 lookat(0.0, 0.0, 0.0);
        vec3 vup(0.0, 1.0, 0.0);
        double dist_to_focus = 10.0;
        double aperture  = 0.1;

        cam = std::make_unique<camera>(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);
        world = std::make_unique<hittable_list>();
        world->random_scene();

        blocks = static_cast<int>(height / thread_num);
        output_color.resize(image_size);
    }

    void Renderer::set_image_size(int width, int height)
    {
        image_width = width;
        image_height = height;
        image_size = width * height;
    }

    void Renderer::set_camera(std::unique_ptr<camera> other_cam)
    {
        cam = std::move(other_cam);
    }

    void Renderer::set_scene(std::unique_ptr<hittable_list> other_world)
    {
        world = std::move(other_world);
    }

    void Renderer::set_scene(std::shared_ptr<hittable> object)
    {
        world->add(object);
    }

    void Renderer::run()
    {
        using double_ms = std::chrono::duration<double, std::milli>;
        auto time_start = std::chrono::steady_clock::now();

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
        for (int j = image_height - 1; j >= 0; --j)
        {
            for (int i = 0; i < image_width; ++i)
            {
                vec3 color(0.0, 0.0, 0.0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / image_width;
                    auto v = (j + random_double()) / image_height;

                    ray r = cam->get_ray(u, v);
                    color += ray_color(r, max_depth);
                }
                color.write_color(std::cout, samples_per_pixel);
                int64_t progress = 100 * speed_of_progress.load() / image_size;
                speed_of_progress++;
                std::cerr << "\rSpeed of Progress: " << progress << '%' << std::flush;
            }
        }

        auto time_end = std::chrono::steady_clock::now();
        double ms = std::chrono::duration_cast<double_ms>(time_end - time_start).count();
        std::cerr << "\nTime elapsed: " << ms << " ms\n" << "Done.\n";
    }

    void Renderer::run_multithreading(int threads)
    {
        if (threads >= std::thread::hardware_concurrency())
        {
            throw std::logic_error("Can not exceed the maximum number of threads!");
        }

        using double_ms = std::chrono::duration<double, std::milli>;
        auto time_start = std::chrono::steady_clock::now();

        thread_num = threads;
        blocks = static_cast<int>(image_height / threads);

        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        std::vector<std::thread> thread_queue(thread_num);
        for (int i = 0; i < thread_num; ++i)
        {
            thread_queue[i] = std::thread(&Renderer::kernel, this, i);
        }
        for (int i = 0; i < thread_num; ++i)
        {
            if (thread_queue[i].joinable())
                thread_queue[i].join();
        }
        for (int i = 0; i < image_size; ++i)
        {
            output_color[i].write_color(std::cout, samples_per_pixel);
        }

        auto time_end = std::chrono::steady_clock::now();
        double ms = std::chrono::duration_cast<double_ms>(time_end - time_start).count();
        terr << "\nTime elapsed: " << ms << " ms\n" << "Done.\n";
    }

    void Renderer::kernel(int index)
    {
        int start = image_height - 1 - blocks * index;
        int end = (index == thread_num - 1) ? -1 : (start - blocks);

        for (int j = start; j > end; --j)
        {
            for (int i = 0; i < image_width; ++i)
            {
                vec3 color(0.0, 0.0, 0.0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = (i + random_double()) / image_width;
                    auto v = (j + random_double()) / image_height;

                    ray r = cam->get_ray(u, v);
                    color += ray_color(r, max_depth);
                }
                // TODO - output color && cerr multithreading safe && std::osyncstream (std::cerr) sin C++20
                int64_t position = image_size - (j + 1) * image_width + i;
                output_color[position] = color;
                int64_t progress = 100 * speed_of_progress.load() / image_size;
                speed_of_progress++;
                terr << "\rSpeed of Progress: " << progress << '%' << std::flush;
            }
        }
    }

    vec3 Renderer::ray_color(const ray& r, int depth)
    {
        hit_record rec;

        // if we have exceeded the ray bounce limit, no more light is gathered
        if (depth <= 0) return vec3(0.0, 0.0, 0.0);

        // hit objects
        if (world->hit(r, 0.001, infinity, rec))
        {
            ray scattered;
            vec3 attenuation;
            if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
                return attenuation * ray_color(scattered, depth - 1);
            return vec3(0.0, 0.0, 0.0);
        }

        // hit background
        vec3 unit_direction = unit_vector(r.direction());
        auto t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}