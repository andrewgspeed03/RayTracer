#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray{
    public:
        ray() {}
        ray(const point3& origin, const point3& direction) : orig(origin), dir(direction) {}
        
        vec3 origin() const {return orig;}
        vec3 direction() const {return dir;}
        vec3 at(float t) const {return orig + t * dir;}

        vec3 orig;
        vec3 dir;
};

#endif