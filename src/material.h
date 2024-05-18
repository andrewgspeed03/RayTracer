#ifndef MATERIALH
#define MATERIALH

class hitRecord;

class material {
    public:
        virtual bool scatter(const ray& rIn, const hitRecord& rec, vec3& attenuation, ray& scattered) const = 0;
};

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