#pragma once
#include <cmath>

struct Vector2 { float x, y; };

struct Matrix4x4 {
    float m[4][4];
};

struct Vector3 {
    float x, y, z;
    float Distance(Vector3 v) {
        return sqrtf(powf(v.x - x, 2) + powf(v.y - y, 2) + powf(v.z - z, 2));
    }
};

inline bool WorldToScreen(Vector3 world, Vector2& screen, Matrix4x4 matrix, int width, int height) {
    float w = matrix.m[0][3] * world.x + matrix.m[1][3] * world.y + matrix.m[2][3] * world.z + matrix.m[3][3];

    if (w < 0.01f) return false;

    float x = matrix.m[0][0] * world.x + matrix.m[1][0] * world.y + matrix.m[2][0] * world.z + matrix.m[3][0];
    float y = matrix.m[0][1] * world.x + matrix.m[1][1] * world.y + matrix.m[2][1] * world.z + matrix.m[3][1];

    screen.x = (width / 2) * (1 + x / w);
    screen.y = (height / 2) * (1 - y / w);

    return true;
}

namespace Memory {
    template <typename T>
    inline T Read(uintptr_t addr) {
        if (!addr) return T();
        return *reinterpret_cast<T*>(addr);
    }

    template <typename T>
    inline void Write(uintptr_t addr, T val) {
        if (!addr) return;
        *reinterpret_cast<T*>(addr) = val;
    }
}
