//
// Created by ZZK on 2022/12/9.
//
#pragma once

#include <OneWeek/vec3.h>
#include <vector>

namespace OneWeek
{
    class perlin
    {
    public:
        perlin();
        ~perlin() = default;

        double noise(const vec3& p) const;
        double turb(const vec3& p, int depth = 7) const;

    private:
        double trilinear_interp(vec3 c[2][2][2], double u, double v, double w) const;
        void perlin_generate_perm();
        static void permute(std::vector<int>& p);

    private:
        static const int point_count;
        std::vector<vec3> ranfloat;
        std::vector<int> perm_x;
        std::vector<int> perm_y;
        std::vector<int> perm_z;
    };
}
