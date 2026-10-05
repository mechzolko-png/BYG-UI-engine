#include "Math.h"
#include <cmath>

float Math::getLength(float x, float y) {
    return std::sqrt(x * x + y * y);
}

Vector2D Math::getNormal(float x, float y, float len) {
    if (len == 0.0f) {
        return {0.0f, 0.0f};
    }

    return {x / len, y / len};
}

float Math::getDistance(float x, float y, float ox, float oy) {
    return Math::getLength(x - ox, y - oy);
}