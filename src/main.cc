#include "constnutil.h"
#include "sphere.h"
#include "hittableList.h"
#include "material.h"

vec3 randomInUnitSphere() {
    vec3 p;
    do 
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    while (p.squaredLength() >= 1.0);
    return p;
}

int main() {

    //Image Properties

    int imageWidth = 256;
    int imageHeight = 256;
    int ns = 100;

    

    float R = cos(M_PI / 4);

    hittable *list[4];
    list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));

    hittable *world = new hittableList(list, 2);
    
    camera cam;
    
    cam.aspectRatio = 16.0 / 9.0;
    cam.imageWidth = 1200;
    cam.samplesPerPixel = 10;
    cam.maxDepth = 20;

    cam.vfov = 20;
    cam.lookFrom = point3(13, 2, 3);
    cam.lookAt = point3(0, 0, 0);
    cam.vUp = vec3(0, 1, 0);

    cam.defocusAngle = 0.6;
    cam.focusAngle = 10.0

    cam.render(world);

}