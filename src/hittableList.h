#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"
#include "constnutil.h"

#include <vector>

class hittableList: public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittableList() {}
        hittableList(shared_ptr<hittable> object) {add(object);}
        
        void clear() {objects.clear();}

        void add(shared_ptr<hittable> object){
            objects.push_back(object);
        }

        virtual bool hit(const ray& r, interval rayT, hitRecord& rec) const override {
            hitRecord tempRec;
            bool hitAnything = false;
            double closestSoFar = rayT.max;

            for (const auto& object : objects)
                if(object -> hit(r, interval(rayT.min, closestSoFar), tempRec)){
                    hitAnything = true;
                    closestSoFar = tempRec.t;
                    rec = tempRec;
                }
    
            return hitAnything;
        }
        
};

#endif