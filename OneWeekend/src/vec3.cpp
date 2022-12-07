//
// Created by ZZK on 2022/12/5.
//

#include <OneWeekend/vec3.h>
#include <OneWeekend/OneWeekendUtils.h>
#include <cmath>

namespace OneWeekend
{
    vec3::vec3() : e{0.0, 0.0, 0.0} {}

    vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    vec3& vec3::operator+=(const vec3& v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& vec3::operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& vec3::operator/=(const double t)
    {
        return *this *= 1/t;
    }

    double vec3::length() const
    {
        return std::sqrt(length_squared());
    }

    double vec3::length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    void vec3::write_color(std::ostream& out, int samples_per_pixel)
    {
        // Divide the color total by the number of samples and gamma-correct
        // for a gamma value 2.0
        auto scale = 1.0 / samples_per_pixel;
        auto r = std::sqrt(scale * e[0]);
        auto g = std::sqrt(scale * e[1]);
        auto b = std::sqrt(scale * e[2]);

        // Write the translated [0,255] value of each color component.
        out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
            << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    }

    vec3 vec3::random()
    {
        return vec3(random_double(), random_double(), random_double());
    }

    vec3 vec3::random(double min, double max)
    {
        return vec3(random_double(min, max), random_double(min, max),
                    random_double(min, max));
    }

    double dot(const vec3& u, const vec3& v)
    {
        return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
    }

    vec3 cross(const vec3& u, const vec3& v)
    {
        return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                    u.e[2] * v.e[0] - u.e[0] * v.e[2],
                    u.e[0] * v.e[1] - u.e[1] * v.e[0]);
    }

    vec3 unit_vector(vec3 v)
    {
        return v / v.length();
    }

    vec3 random_unit_sphere()
    {
        while (true)
        {
            auto p = vec3::random(-1, 1);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }

    vec3 random_unit_vector()
    {
        auto a = random_double(0, 2 * pi);
        auto z = random_double(-1, 1);
        auto r = std::sqrt(1 - z * z);
        return vec3(r * std::cos(a), r * sin(a), z);
    }

    vec3 random_in_hemisphere(const vec3& normal)
    {
        vec3 in_unit_sphere = random_unit_sphere();
        if (dot(in_unit_sphere, normal) > 0.0)
            return in_unit_sphere;
        else
            return -in_unit_sphere;
    }

    vec3 reflect(const vec3& v, const vec3& n)
    {
        return v - 2 * dot(v, n) * n;
    }

    vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat)
    {
        auto cos_theta = dot(-uv, n);
        vec3 r_out_parallel = etai_over_etat * (uv + cos_theta * n);
        vec3 r_out_perp = -std::sqrt(1.0 - r_out_parallel.length_squared()) * n;
        return r_out_parallel + r_out_perp;
    }

    double schlick(double cosine, double ref_idx)
    {
        auto r0 = (1 - ref_idx) / (1 + ref_idx);
        r0 = r0 * r0;
        return r0 + (1 - r0) * std::pow((1 - cosine), 5);
    }

    vec3 random_in_unit_disk()
    {
        while (true)
        {
            auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
            if (p.length_squared() >= 1) continue;
            return p;
        }
    }
}






