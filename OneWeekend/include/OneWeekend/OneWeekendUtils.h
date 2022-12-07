//
// Created by ZZK on 2022/12/5.
//

#pragma once

#include <cmath>
#include <limits>
#include <random>
#include <functional>

namespace OneWeekend
{
    // Constants
    const double infinity = std::numeric_limits<double>::infinity();
    const double pi = 3.1415926535897932385;

    // Utility functions
    inline double degree_to_radians(double degrees) {
        return degrees * pi / 180.0;
    }

    inline double ffmin(double a, double b) { return a <= b ? a : b; }

    inline double ffmax(double a, double b) { return a >= b ? a : b; }

    inline double clamp(double x, double min, double max) {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    inline double random_double() {
        // Returns a random real in [0, 1)
        // return rand() / (RAND_MAX + 1.0);
        static std::uniform_real_distribution<double> distribution(0.0, 1.0);
        static std::mt19937 generator;
        static std::function<double()> rand_generator =
                std::bind(distribution, generator);
        return rand_generator();
    }

    inline double random_double(double min, double max) {
        // Returns a random real in [min, max)
        return min + (max - min) * random_double();
    }
}
























