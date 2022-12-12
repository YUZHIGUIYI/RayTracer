//
// Created by ZZK on 2022/12/9.
//

#include <OneWeek/aabb.h>
#include <OneWeek/OneWeekUtils.h>

namespace OneWeek
{
    aabb::aabb(const vec3& a, const vec3& b) : _min(a), _max(b) {}

    vec3 aabb::min() const { return _min; }

    vec3 aabb::max() const { return _max; }

    bool aabb::hit(const OneWeek::ray &r, double tmin, double tmax) const
    {
        for (int a = 0; a < 3; ++a)
        {
            // old method
//            auto t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a],
//                            (_max[a] - r.origin()[a]) / r.direction()[a]);
//            auto t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a],
//                            (_max[a] - r.origin()[a]) / r.direction()[a]);
//            tmin = ffmax(t0, tmin);
//            tmax = ffmin(t1, tmax);
//            if (tmax <= tmin)
//                return false;
            // another method - work better
            auto invD = 1.0f / r.direction()[a];
            auto t0 = (min()[a] - r.origin()[a]) * invD;
            auto t1 = (max()[a] - r.origin()[a]) * invD;
            if (invD < 0.0)
            {
                std::swap(t0, t1);
            }
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if (tmax <= tmin)
            {
                return false;
            }
        }
        return true;
    }

    aabb aabb::surrounding_box(const aabb &box0, const aabb &box1)
    {
        vec3 small(ffmin(box0.min().x(), box1.min().x()),
                    ffmin(box0.min().y(), box1.min().y()),
                    ffmin(box0.min().z(), box1.min().z()));
        vec3 big(ffmax(box0.max().x(), box1.max().x()),
                    ffmax(box0.max().y(), box1.max().y()),
                    ffmax(box0.max().z(), box1.max().z()));
        return aabb{small, big};
    }
}
























