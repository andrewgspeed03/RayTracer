#include <iostream>

int main() {
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int y = ny-1; y >= 0; y--){
        for (int x = 0; x < nx; x++){
            float r = float(x) / float(nx);
            float g = float(y) / float(ny);
            float b = 0.2;

            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);

            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}