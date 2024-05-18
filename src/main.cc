#include <iostream>
#include <cstdlib>
#include "sphere.h"
#include "hittableList.h"
#include "float.h"
#include "camera.h"


vec3 color(const ray& r, hittable *world){
    hitRecord rec;
    if (world -> hit(r, 0.0, MAXFLOAT, rec))
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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
            for (int s = 0; s < ns; s ++){
                float u = float(x + drand48()) / float(nx);
                float v = float(y + drand48()) / float(ny);
                ray r = cam.getRay(u, v);
                vec3 p = r.pointAtParameter(2.0);
                col += color(r, world);
            }
            col /= float(ns);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}