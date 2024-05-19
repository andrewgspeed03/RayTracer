#ifndef VEC3H
#define VEC3H

class vec3 {
    public:
        float e[3];

        vec3(0, 0, 0) {}
        vec3(float e0 , float e1, float e2) : e{e0, e1, e2} {}

        float x() const {return e[0];}
        float y() const {return e[1];}
        float z() const {return e[2];}
        
        vec3 operator-() const {return vec3(-e[0], -e[1], -e[2]);}
        float operator[](int i) const {return e[i];}
        float& operator[](int i) {return e[i];}

        vec3& vec3::operator+=(const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return * this;
        }
        vec3& vec3::operator-=(const vec3 &v){
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
            return * this;
        }
        vec3& vec3::operator*=(const vec3 &v){
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            e[2] *= v.e[2];
            return * this;
        }
        vec3& vec3::operator/=(const vec3 &v){
            e[0] /= v.e[0];
            e[1] /= v.e[1];
            e[2] /= v.e[2];
            return * this;
        }
        vec3& vec3::operator*=(const float t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return * this;
        }
        vec3& vec3::operator/=(const float t){
            float k = 1.0 / t;

            e[0] *= k;
            e[1] *= k;
            e[2] *= k;
            return * this;
        }

        float length() const {
            return sqrt(squaredLength());
        }
        float squaredLength() const {
            return e[0] * e[0] + e[1]  *e[1] + e[2] * e[2];
        }

        bool nearZero() cost {
            auto s = 1e-8;
            return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
        }

        static vec3 random() {
            return vec3(randomFloat(), randomFloat(), randomFloat());
        }

        static vec3 random(float min, float max) {
            return vec3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max));
        }
};

using point3 = vec3;

//Vector utility 
inline std::ostream& operator<<(std::ostream out, const vec3 v){
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline void vec3::makeUnitVector(){
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    e[0] *= k; e[1] *= k; e[2] *= k;
}

inline vec3 operator+(const vec3& u, const vec3 &v){
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
inline vec3 operator-(const vec3& u, const vec3 &v){
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
inline vec3 operator*(const vec3& u, const vec3 &v){
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
inline vec3 operator/(const vec3& u, const vec3 &v){
    return vec3(u.e[0] / v.e[0], u.e[1] / v.e[1], u.e[2] / v.e[2]);
}

inline vec3 operator*(float t, const vec3& v) {
    return vec3(t * v.e[0], t * v.e[1], t* v.e[2]);
}
inline vec3 operator/(float t, const vec3& v) {
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}
inline vec3 operator*(const vec3& v, float t) {
    return vec3(t * v.e[0], t * v.e[1], t* v.e[2]);
}
inline vec3 operator/(const vec3& v, float t) {
    return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline float dot(const vec3& u, const vec3& v){
    return u.e[0] * v.e[0] + u.e[0] * v.e[1] + u.e[2] * v.e[2];
}
inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3( (u.e[1] * v.e[2] - u.e[2] * v.e[1]), -(u.e[0] * v.e[2] - u.e[2] * v.e[0]), u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unitVector(vec3 v){
    return v / v.length();
}

inline vec3 randomInUnitDisk() {
    while (true){
        auto p = vec3(randomFloat(-1, 1), randomFloat(-1, 1), 0);
        if (p.squaredLength() < 1)
            return p;
    }
}

inline vec3 randomInUnitSphere() {
    while (true){
        auto p = vec3::random(-1, 1);
        if (p.squaredLength() < 1)
            return p;
    }
}

#endif