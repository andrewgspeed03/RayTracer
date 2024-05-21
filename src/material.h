#ifndef MATERIALH
#define MATERIALH

#include "constnutil.h"

class hitRecord;

class material {
    public:
        virtual ~material() = default;

        virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& attenuation, ray& scattered) const {return false;}
};

class lambertian : public material {
    public:
        lambertian(const color& a) : albedo(a) {}
        
        virtual bool scatter(const ray& rIn, const hitRecord rec, color& attenuation, ray& scattered) const override{
            auto scatterDirection = rec.normal + randomUnitVector();

            if (scatterDirection.near_zero())
                scatterDirection = rec.normal;

            scattered = ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;           
        }

    private:
        color albedo;
};

class metal : public material {
    public:
        metal(const color& albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz: 1) {}

        bool scatter(const ray& rIn, const hitRecord& rec, color& attenuation, ray& scattered) const override{
            vec3 reflected = reflect(rIn.direction(), rec.normal);
            reflected = unitVector(reflected) + (fuzz * randomUnitVector());
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    private:
        color albedo;
        float fuzz;
};

class dielectric : public material {
    public:
        dielectric(float refractionIndex) : refractionIndex(refractionIndex) {}

        bool scatter(const ray& rIn, const hitRecord rec, color& attenuation, ray& scattered) const override{
            attenuation = color(1.0, 1.0, 1.0);
            float ri = rec.frontFace ? (1.0 / refractionIndex) : refractionIndex;

            vec3 unitDirection = unitVector(rIn.direction());
            float cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
            float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

            bool cannotRefract = ri * sinTheta > 1.0;
            vec3 direction;

            if (cannotRefract || reflectance(cosTheta, ri) > randomFloat())
                direction = reflect(unitDirection, rec.normal);
            else
                direction = refract(unitDirection, rec.normal, ri);

            scattered = ray(rec.p, direction);
            return true;
        }
    
    private:
        float refractionIndex

        static float reflectance(float cosine, float refractionIndex){
            auto r0 = (1 - refractionIndex) / (1 + refractionIndex);
            r0 = r0 * r0;
            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }
};

#endif