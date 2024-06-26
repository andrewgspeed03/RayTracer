#ifndef HITTABLEH
#define HITTABLEH

#include "constnutil.h"

class material;

struct hitRecord {
    point3 p;
    vec3 normal;
    shared_ptr<material> mat;
    float t;
    bool frontFace;

    void setFaceNormal(const ray& r, const vec3& outwardNormal){
        //sets the hit record normal vector

        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
class hittable{
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const = 0;
};

#endif