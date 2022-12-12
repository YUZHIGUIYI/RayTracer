//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/perlin.h>
#include <OneWeek/OneWeekUtils.h>

namespace OneWeek
{
    const int perlin::point_count = 256;

    perlin::perlin()
    {
        ranfloat.reserve(point_count);
        perm_x.reserve(point_count);
        perm_y.reserve(point_count);
        perm_z.reserve(point_count);

        for (int i = 0; i < point_count; ++i)
        {
            ranfloat[i] = unit_vector(vec3::random(-1, 1));
        }

        perlin_generate_perm();
    }

    double perlin::noise(const vec3 &p) const
    {
        auto u = p.x() - std::floor(p.x());
        auto v = p.y() - std::floor(p.y());
        auto w = p.z() - std::floor(p.z());

        // hermite cube to smooth difference
//        u = u * u * (3.0 - 2.0 * u);
//        v = v * v * (3.0 - 2.0 * v);
//        w = w * w * (3.0 - 2.0 * w);

        int i = static_cast<int>(std::floor(p.x()));
        int j = static_cast<int>(std::floor(p.y()));
        int k = static_cast<int>(std::floor(p.z()));

        vec3 c[2][2][2];

        for (int di = 0; di < 2; ++di)
        {
            for (int dj = 0; dj < 2; ++dj)
            {
                for (int dk = 0; dk < 2; ++dk)
                {
                    c[di][dj][dk] = ranfloat[
                            perm_x[(i + di) & 255] ^
                            perm_y[(j + dj) & 255] ^
                            perm_z[(k + dk) & 255]];
                }
            }
        }

        return trilinear_interp(c, u, v, w);
    }

    void perlin::perlin_generate_perm()
    {
        for (int i = 0; i < point_count; ++i)
        {
            perm_x[i] = i;
            perm_y[i] = i;
            perm_z[i] = i;
        }

        permute(perm_x);
        permute(perm_y);
        permute(perm_z);
    }

    void perlin::permute(std::vector<int> &p)
    {
        for (int i = point_count - 1; i > 0; --i)
        {
            int target = random_int(0, i);
            int tmp = p[i];
            p[i] = p[target];
            p[target] = tmp;
        }
    }

    double perlin::trilinear_interp(vec3 c[2][2][2], double u, double v, double w) const
    {
        double accum = 0.0;
        double uu = u * u * (3.0 - 2.0 * u);
        double vv = v * v * (3.0 - 2.0 * v);
        double ww = w * w * (3.0 - 2.0 * w);

        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 2; ++j)
            {
                for (int k = 0; k < 2; ++k)
                {
                    vec3 weight_v(u - i, v - j, w - k);
                    accum += (i * uu + (1 - i) * (1- uu)) * (j * vv + (1 - j) * (1- vv)) *
                            (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_v);
                }
            }
        }

        return accum;
    }

    double perlin::turb(const vec3 &p, int depth) const
    {
        double accum = 0.0;
        vec3 temp_p = p;
        auto weight = 1.0;

        for (int i = 0; i < depth; ++i)
        {
            accum += weight * noise(temp_p);
            weight *= 0.5;
            temp_p *= 2;
        }

        return std::abs(accum);
    }
}
























