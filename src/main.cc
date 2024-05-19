#include <iostream>
#include <cstdlib>

#include "color.h"
#include "sphere.h"
#include "hittableList.h"
#include "float.h"
#include "camera.h"
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

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

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

    //renderer

    for (int y = imageHeight-1; y >= 0; y--){

        //progress bar
        std::clog << "\rScanlines remaining: " << (imageHeight - y) << " " << std::flush;

        for (int x = 0; x < imageWidth; x++){
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s ++){
                float u = float(x + drand48()) / float(imageWidth);
                float v = float(y + drand48()) / float(imageHeight);
                ray r = cam.getRay(u, v);
                vec3 p = r.pointAtParameter(2.0);
                col += color(r, world);
            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]))

            auto pixelColor = color(float(x) / (imageWidth - 1), float(y) / ( imageHeight - 1), 0);
            writeColor(std::cout, pixelColor);
        }
    }

    std::clog << "\rDone.                \n";
}