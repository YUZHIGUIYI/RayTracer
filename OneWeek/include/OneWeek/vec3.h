//
// Created by ZZK on 2022/12/8.
//
#pragma once

#include <ostream>

namespace OneWeek
{
    class vec3
    {
    public:
        vec3();
        vec3(double e0, double e1, double e2);

    public:
        inline double x() const { return e[0]; }
        inline double y() const { return e[1]; }
        inline double z() const { return e[2]; }

        inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        inline double operator[](size_t i) const { return e[i]; }
        inline double& operator[](size_t i) { return e[i]; }

    public:
        vec3& operator+=(const vec3& v);
        vec3& operator*=(const double t);
        vec3& operator/=(const double t);

        double length() const;
        double length_squared() const;

        void write_color(std::ostream& out, int samples_per_pixel);

    public:
        friend std::ostream& operator<<(std::ostream& out, const vec3& v)
        {
            return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        }

        friend vec3 operator+(const vec3& u, const vec3& v)
        {
            return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
        }

        friend vec3 operator-(const vec3& u, const vec3 &v)
        {
            return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
        }

        friend vec3 operator*(const vec3& u, const vec3& v)
        {
            return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
        }

        friend vec3 operator*(double t, const vec3& v)
        {
            return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
        }

        friend vec3 operator*(const vec3& v, double t)
        {
            return t * v;
        }

        friend vec3 operator/(vec3 v, double t)
        {
            return (1 / t) * v;
        }

    public:
        static vec3 random();
        static vec3 random(double min, double max);

    public:
        double e[3];
    };

    double dot(const vec3& u, const vec3& v);
    vec3 cross(const vec3& u, const vec3& v);
    vec3 unit_vector(vec3 v);
    vec3 random_unit_sphere();
    vec3 random_unit_vector();
    vec3 random_in_hemisphere(const vec3& normal);
    vec3 reflect(const vec3& v, const vec3& n);
    vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat);
    double schlick(double cosine, double ref_idx);
    vec3 random_in_unit_disk();
}
















