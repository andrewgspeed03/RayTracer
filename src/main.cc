#include <iostream>
#include <cstdlib>
#include "sphere.h"
#include "hittableList.h"
#include "float.h"
#include "camera.h"

vec3 randomInUnitSphere() {
    vec3 p;
    do 
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
    while (p.squaredLength() >= 1.0);
    return p;
}

vec3 color(const ray& r, hittable *world){
    hitRecord rec;
    if (world -> hit(r, 0.0, MAXFLOAT, rec)){
        vec3 target = rec.p + rec.normal + randomInUnitSphere();
        return 0.5 * color( ray(rec.p, targer - rec.p), world);
    }
    else{
        vec3 unitDirection = unitVector(r.direction());
        float t = 0.5 * (unitDirection.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 200;
    int ny = 100;
    int ns = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    hittable *list[2];
    list[0] = new sphere(vec3(0, 0, -1), 0.5);
    list[1] = new sphere(vec3(0, -100.5, -1), 100);
    hittable *world = new hittableList(list, 2);

    camera cam;
    for (int y = ny-1; y >= 0; y--){
        for (int x = 0; x < nx; x++){
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s ++){
                float u = float(x + drand48()) / float(nx);
                float v = float(y + drand48()) / float(ny);
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
}