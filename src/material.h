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

bool refract(const vec3& v, const vec3& n, float niOverNt, vec3& refracted){
    vec3 uv = unitVector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - niOverNt * niOverNt * (1 - dt * dt);
    
    if (discriminant > 0){
        refracted =niOverNt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    }
    else
        return false;
}

class dielectric : public material {
    public:
        dielectric(float ri) ; refIdx(ri){}

        virtual bool scatter(const ray& rIn, const hitRecord rec, vec3& attenuation, ray& scattered) const{
            vec3 outwardNormal;
            vec3 reflected = reflect(rIn.direction(), rec.normal);
            float niOverNt;
            attenuation = vec3(1.0, 1.0, 0.0);
            vec3 refracted;
            if (dot(rIn.direction(), rec.normal) > 0) {
                outwardNormal = -rec.normal;
                niOverNt = refIdx;
            }
            else{
                outwardNormal = rec.normal;
                niOverNt = 1.0 / refIdx;
            }
            if (refract(rIn.direction(), outwardNormal, niOverNt, refracted)) {
                scattered = ray(rec.p, refracted);
            }
            else {
                scattered = ray(rec.p, reflected);
                return false;
            }
            return true;
        }

        float refIdx;
}

#endif