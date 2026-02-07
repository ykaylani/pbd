#ifndef TYPES
#define TYPES
#include <cmath>
#include <math.h>

struct float3 {
    float x, y, z;

    float3 operator*(float other) const {
        return {x * other, y * other, z * other};
    }

    friend float3 operator*(float scalar, const float3& vec) {
        return {scalar * vec.x, scalar * vec.y, scalar * vec.z};
    }

    float3 operator+(const float3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    float3 operator-(const float3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    float3 operator/(float other) const {
        return {x / other, y / other, z / other};
    }

    float3 operator/(float3 other) const {
        return {x / other.x, y / other.y, z / other.z};
    }

    static float dot(const float3& a, const float3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    static float magnitude(const float3& a) {
        return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    static float3 unit(const float3 &a) {
        return {a.x / magnitude(a.x), a.x / magnitude(a.z), a.x / magnitude(a.z)};
    }

};

#endif //TYPES