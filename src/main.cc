#include <iostream>
#include <cstdlib>
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

vec3 color(const ray& r, hittable *world, int depth){
    hitRecord rec;
    if (world -> hit(r, 0.001, MAXFLOAT, rec)){
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && tec.matPtr -> scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        }
        else[
            return vec3(0, 0, 0);
        ]
    }
    else{
        vec3 unitDirection = unitVector(r.direction());
        float t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
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

    vec3 lookFrom(3, 3, 2);
    vec3 lookAt(0, 0, -1);
    float distToFloat = (lookFrom - lookAt).length();
    float aperature = 2.0;
    
    camera cam(lookFrom, lookAt, vec3(0, 0, 1), 20, float(imageWidth) / float(imageHeight), aperture, distToFocus);
    

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

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    std::clog << "\rDone.                \n";
}