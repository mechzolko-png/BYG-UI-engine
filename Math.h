#pragma once
#ifndef BYG_UI_ENGINE_MATH_H
#define BYG_UI_ENGINE_MATH_H

struct Vector2D {
    float x;
    float y;
};

class Math {
    public:
    static float getLength(float x, float y);
    static Vector2D getNormal(float x, float y, float len);
    static float getDistance(float x, float y, float ox, float oy);
};

#endif
