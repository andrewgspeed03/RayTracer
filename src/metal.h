#ifndef METALH
#define METALH

#include "material.h"

class metal : public material {
    public:
        metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1;}
        virtual bool scatter(const ray& rIn, const hitRecord rec, vec3& attenuation, ray& scattered) const {
            vec3 reflected = reflect(unitVector(rIn.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

        vec3 albedo;
        float fuzz;
} 

#endif