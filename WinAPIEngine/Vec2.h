#pragma once
#include "Vec3.h"

class Vec2 {
public:
    float x;
    float y;

    Vec2(float x, float y);

    Vec2(Vec3 vec);
};

