#ifndef CONSTNUTILH
#define CONSTNUTILH

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

//STD usings
using std::fabs;
using std::make_shared;
using std::shared_ptr;
using std::sqrt;

//constants

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926535897932385;

//Utility Functions

inline float degreesToRadians(float degrees){
    return degrees * pi / 180.0;
}

inline float randomFloat() {
    return rand() / (RAND_MAX + 1.0);
}

inline float randomFloat(float min, float max) {
    return min + (max - min) * randomFloat();
}

//common headers

#include "color.h"
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif