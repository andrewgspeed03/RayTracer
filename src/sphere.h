#ifndef SPHEREH
#define SPHEREH

#include "hittable.h"

class sphere: public hittable {
    public:
        sphere() {}
        sphere(vec3 cen, float r) : center(cen), radius(r) {};
        
        virtual bool hit(const ray& r, float tMin, float tMax, hitRecord& rec) const;
        
        vec3 center;
        float radius;
};

bool sphere::hit(const ray& r, float tMin, float tMax, hitRecord& rec) const {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant > 0){
        float temp = (-b - sqrt(b * b - a * c) )/ a;
        if (temp < tMax && temp > tMin) {
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin){
            rec.t = temp;
            rec.p = r.pointAtParameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
    }
    return false;
}    
       
#endif