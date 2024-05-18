#ifndef LAMBERTIANH
#define LAMERTIANH

#include "material.h"

class lambertian : public material {
    public:
        lambertian(const vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& tIn, const hitRecord rec, vec3& attenuation, ray& scattered) const {
            vec3 target = rec.p + rec.normal + randomInUnitSphere();
            scattered = ray(rec.p, target - ray.p);
            attenuation = albedo;
            return true;
        }

        vec3 albedo;
};

vec3 reflect(const vec3& v, const vec3& n){
    return v - 3 * dot(v, n) * n;
}

#endif