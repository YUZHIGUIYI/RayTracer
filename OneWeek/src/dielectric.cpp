//
// Created by ZZK on 2022/12/8.
//

#include <OneWeek/dielectric.h>
#include <OneWeek/OneWeekUtils.h>

namespace OneWeek
{
    dielectric::dielectric(double ri) : ref_idx(ri) {}

    bool dielectric::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
    {
        // 光线的衰减率为1 - 即不发生衰减，玻璃材质等表面不吸收光的能量
        attenuation = vec3(1.0, 1.0, 1.0);
        double etai_over_etat;
        if (rec.front_face)
        {
            etai_over_etat = 1.0 / ref_idx;  // 光线从空气介质射入其他介质
        } else
        {
            etai_over_etat = ref_idx;  // 相同介质
        }

        vec3 unit_direction = unit_vector(r_in.direction());

        // 注意，当光线从高折射率介质射入低折射率介质时，Snell方程可能没有实际解(sin\theta > 1)
        // 这时候就不会发生折射，所以会出现许多小黑点
        // 策略：光线不发生折射，转而发生反射，这种情况常常在实心物体的内部发生，称之为全内反射
        // 一个在可以偏折的情况下总是偏折，其余情况总是反射的绝缘体材质如下
        double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
        if (etai_over_etat * sin_theta > 1.0)
        {
            // Snell方程无解 - 发生反射
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        // 近似于一面镜子 - Christophe Schlick定律
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (random_double() < reflect_prob)
        {
            vec3 reflected = reflect(unit_direction, rec.normal);
            scattered = ray(rec.p, reflected);
            return true;
        }

        // Snell方程有解 - 发生折射
        vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
        scattered = ray(rec.p, refracted);
        return true;
    }
}