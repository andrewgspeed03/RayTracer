#ifndef COLORH
#define COLORH

#include "vec3.h"

#include <iostream>

using color = vec3

void writeColor(std::ostream& out, const color& pixelColor){
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    int rByte = int(255.99 * r);
    int gByte = int(255.99 * g);
    int bByte = int(255.99 * b);

    out << rByte << " " << gByte << " " << bByte << "\n";
}

#endif