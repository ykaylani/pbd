#ifndef TYPES
#define TYPES
#include <cmath>

struct float3 {
    float x, y, z;

    float3 operator*(float other) const {
        return {x * other, y * other, z * other};
    }

    float3 operator*(const float3& vec) const {
        return {x * vec.x, y * vec.y, z * vec.z};
    }

    float3 operator+(const float3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    float3 operator+(const float& other) const {
        return {x + other, y + other, z + other};
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
        return std::sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    }

    static float sqrMagnitude(const float3& a) {
        return a.x * a.x + a.y * a.y + a.z * a.z;
    }

    static float3 unit(const float3 &a) {
        float mag = magnitude(a);
        return {a.x / mag, a.y / mag, a.z / mag};
    }

    static float3 cross(const float3& a, const float3& b) {
        return {(a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x  * b.z), (a.x * b.y) - (a.y  * b.x)};
    }
};

inline float3 operator*(const float& a, const float3& b) {
    return {a * b.x, a * b.y, a * b.z};
}

#endif //TYPES