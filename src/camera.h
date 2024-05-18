#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
    public:
        camera(float vfov, float aspect) {
            float theta = vfov * M_PI / 180;
            float halfHeight = tan(theta / 2);
            float halfWidth = aspect * halfHeight;
            lowerLeftCorner = vec3(-halfWidth, -halfWidth, -1.0);
            horizontal = vec3(1 * halfWidth, 0.0, 0.0);
            vertical = vec3(0.0, 2 * halfHeight, 0.0);
            origin = vec3(0.0, 0.0, 0.0);
        }

        ray getRay(float u, float v) {ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);}

        vec3 origin;
        vec3 lowerLeftCorner;
        vec3 horizontal;
        vec3 vertical;
};

#endif