#ifndef SPHEREH
#define SPHEREH

#include "hittable.h"

class sphere: public hittable {
    public:
        sphere() {}
        sphere(const point3& cen, float r, shared_ptr<material> m) : center(cen), radius(fmax(0, r)), material(m){};
        
        virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const override{
            vec3 oc = r.origin() - center;
            auto a = dot(r.direction(), r.direction());
            auto h = dot(oc, r.direction());
            auto c = oc.lengthSquared() - radius * radius;
            
            auto discriminant = h * h - a * c;

            if (discriminant < 0)
                return false;
            
            auto sqrtd = sqrt(discriminant);

            //find nearest root within range
            auto root = (h - sqrtd) / a;
            if (!rayT.surrounds(root)){
                root = (h + sqrtd) / a;
                if (!rayT.surrounds(root))
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            vec3 outwardNormal = (rec.p - center) / radius;
            rec.setFaceNormal(r, outwardNormal);
            rec.mat = mat;

            return true;
        }

    private:
        point3 center;
        float radius;
        shared_ptr<material> mat;
};
      
#endif